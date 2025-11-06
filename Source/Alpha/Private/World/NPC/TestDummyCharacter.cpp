// TestDummyCharacter.cpp
#include "World/NPC/TestDummyCharacter.h"   
#include "Components/StatsComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/HUD/StatsWidget.h"

ATestDummyCharacter::ATestDummyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));

    // ✅ używamy pola klasy
    StatsWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatsWidgetComponent"));
    StatsWidgetComponent->SetupAttachment(RootComponent);

    StatsWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
    StatsWidgetComponent->SetDrawAtDesiredSize(true);
    StatsWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
    StatsWidgetComponent->SetWidgetClass(UStatsWidget::StaticClass());
    
}


void ATestDummyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (StatsWidgetComponent)
    {
        if (UStatsWidget* StatsWidget = Cast<UStatsWidget>(StatsWidgetComponent->GetUserWidgetObject()))
        {
            StatsWidget->InitializeWidget(StatsComponent);
        }
    }

    if (StatsComponent)
    {
        StatsComponent->OnHealthChanged.AddDynamic(this, &ATestDummyCharacter::OnHealthChanged);
        StatsComponent->OnDeath.AddDynamic(this, &ATestDummyCharacter::OnDeath);
    }
}

void ATestDummyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!StatsWidgetComponent) return;

    if (APlayerCameraManager* CamMgr = UGameplayStatics::GetPlayerCameraManager(this, 0))
    {
        FVector CamLoc = CamMgr->GetCameraLocation();
        FVector ToCam = CamLoc - StatsWidgetComponent->GetComponentLocation();
        FRotator LookRot = FRotationMatrix::MakeFromX(ToCam).Rotator();
        StatsWidgetComponent->SetWorldRotation(LookRot);

        // --- FADING ---

        float Distance = FVector::Dist(CamLoc, GetActorLocation());

        float TargetOpacity = 1.0f;

        if (Distance > WidgetFadeStartDistance)
        {
            float Alpha = FMath::Clamp(
                1.0f - (Distance - WidgetFadeStartDistance) / (WidgetFadeEndDistance - WidgetFadeStartDistance),
                0.0f,
                1.0f
            );
            TargetOpacity = Alpha;
        }

        // Bierzemy sam widget z komponentu
        if (UUserWidget* Widget = Cast<UUserWidget>(StatsWidgetComponent->GetUserWidgetObject()))
        {
            float CurrentOpacity = Widget->GetRenderOpacity();
            float NewOpacity = FMath::FInterpTo(CurrentOpacity, TargetOpacity, DeltaTime, WidgetFadeSpeed);
            Widget->SetRenderOpacity(NewOpacity);

            bool bShouldBeVisible = NewOpacity > 0.01f;
            StatsWidgetComponent->SetVisibility(bShouldBeVisible);
        }
    }
}




float ATestDummyCharacter::TakeDamage(
    float DamageAmount,
    FDamageEvent const& DamageEvent,
    AController* EventInstigator,
    AActor* DamageCauser
)
{
    // Najpierw niech bazowa implementacja zrobi swoje (np. hit reactions itp.)
    const float SuperDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    const float FinalDamage = SuperDamage > 0.f ? SuperDamage : DamageAmount;

    if (StatsComponent && FinalDamage > 0.f)
    {
        StatsComponent->TakeDamage(FinalDamage, EventInstigator);
    }

    return FinalDamage;
}

void ATestDummyCharacter::OnHealthChanged(const float NewHealth, const float Delta)
{
    UE_LOG(LogTemp, Log, TEXT("Dummy HP: %f (%+f)"), NewHealth, Delta);
}

void ATestDummyCharacter::OnDeath(AActor* DeadActor)
{
    UE_LOG(LogTemp, Warning, TEXT("Dummy died: %s"), *GetName());

    // Proste ragdoll
    if (USkeletalMeshComponent* MeshComp = GetMesh())
    {
        MeshComp->SetSimulatePhysics(true);
        MeshComp->SetCollisionProfileName(FName("Ragdoll"));
    }

    if (UCapsuleComponent* Capsule = GetCapsuleComponent())
    {
        Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

    // Auto-destroy po kilku sekundach (dla porządku)
    SetLifeSpan(10.f);
}
