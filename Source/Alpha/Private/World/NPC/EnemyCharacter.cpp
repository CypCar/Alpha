#include "World/NPC/EnemyCharacter.h"          // dopasuj ścieżkę do swojego folderu
#include "Components/StatsComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/HUD/StatsWidget.h"
#include "AIController.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Stats
	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));

	// Widget nad głową
	StatsWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatsWidgetComponent"));
	StatsWidgetComponent->SetupAttachment(RootComponent);
	StatsWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	StatsWidgetComponent->SetDrawAtDesiredSize(true);
	StatsWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
	// Klasy widgetu nie wymuszam tu – ustawisz w BP:
	// StatsWidgetComponent->SetWidgetClass(UStatsWidget::StaticClass());

	// Kolizja & ruch – klasyczny enemy, blokuje gracza
	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Capsule->SetCollisionObjectType(ECC_Pawn);

	}

	if (UCharacterMovementComponent* Move = GetCharacterMovement())
	{
		Move->bOrientRotationToMovement = true;
		Move->RotationRate = FRotator(0.f, 540.f, 0.f);
	}
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Podpięcie widgetu do StatsComponent
	if (StatsWidgetComponent)
	{
		if (UStatsWidget* StatsWidget = Cast<UStatsWidget>(StatsWidgetComponent->GetUserWidgetObject()))
		{
			StatsWidget->InitializeWidget(StatsComponent);
		}
	}

	// Podpięcie delegatów
	if (StatsComponent)
	{
		StatsComponent->OnHealthChanged.AddDynamic(this, &AEnemyCharacter::OnHealthChanged);
		StatsComponent->OnDeath.AddDynamic(this, &AEnemyCharacter::OnDeath);
	}
}

float AEnemyCharacter::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser
)
{
	if (bIsDead || DamageAmount <= 0.f || !StatsComponent)
	{
		return 0.f;
	}

	const float SuperDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	const float FinalDamage = SuperDamage > 0.f ? SuperDamage : DamageAmount;

	if (FinalDamage > 0.f)
	{
		StatsComponent->TakeDamage(FinalDamage, EventInstigator);
	}

	return FinalDamage;
}

void AEnemyCharacter::OnHealthChanged(float NewHealth, float Delta)
{
	// Debug
	UE_LOG(LogTemp, Log, TEXT("Enemy %s HP: %f (%+f)"), *GetName(), NewHealth, Delta);
}

void AEnemyCharacter::OnDeath(AActor* DeadActor)
{
	if (bIsDead) return;
	bIsDead = true;

	UE_LOG(LogTemp, Warning, TEXT("Enemy %s died"), *GetName());

	// Wyłącz sterowanie ruchem
	if (UCharacterMovementComponent* Move = GetCharacterMovement())
	{
		Move->DisableMovement();
		Move->StopMovementImmediately();
	}

	// Odłącz AIController (przestaje myśleć)
	if (AAIController* AICont = Cast<AAIController>(GetController()))
	{
		AICont->StopMovement();
	}

	// Ragdoll
	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetSimulatePhysics(true);
		MeshComp->SetCollisionProfileName(FName("Ragdoll"));
	}

	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// Auto-destroy po kilku sekundach
	SetLifeSpan(10.f);
}

float AEnemyCharacter::GetHealthPercent() const
{
	return StatsComponent ? StatsComponent->GetHealthPercentage() : 0.f;
}
