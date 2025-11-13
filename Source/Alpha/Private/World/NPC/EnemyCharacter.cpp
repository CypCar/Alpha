#include "World/NPC/EnemyCharacter.h"
#include "Components/StatsComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/HUD/StatsWidget.h"
#include "AIController.h"

//==========================================================================
// CONSTRUCTOR
//==========================================================================
AEnemyCharacter::AEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Stats Component Setup
    StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));

    // Widget Component Setup
    StatsWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatsWidgetComponent"));
    StatsWidgetComponent->SetupAttachment(RootComponent);
    StatsWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
    StatsWidgetComponent->SetDrawAtDesiredSize(true);
    StatsWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
    // Widget class set in BP: StatsWidgetComponent->SetWidgetClass(UStatsWidget::StaticClass());

    // Collision & Movement Setup
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

//==========================================================================
// GAME FLOW
//==========================================================================
void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Initialize Stats Widget
    if (StatsWidgetComponent)
    {
        if (UStatsWidget* StatsWidget = Cast<UStatsWidget>(StatsWidgetComponent->GetUserWidgetObject()))
        {
            StatsWidget->InitializeWidget(StatsComponent);
        }
    }

    // Bind Stats Component Events
    if (StatsComponent)
    {
        StatsComponent->OnHealthChanged.AddDynamic(this, &AEnemyCharacter::OnHealthChanged);
        StatsComponent->OnDeath.AddDynamic(this, &AEnemyCharacter::OnDeath);
    }
}

void AEnemyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!StatsWidgetComponent) return;

    //==========================================================================
    // WIDGET ROTATION & FADING SYSTEM
    //==========================================================================
    if (const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0))
    {
        const FVector CameraLocation = CameraManager->GetCameraLocation();
        const FVector ToCamera = CameraLocation - StatsWidgetComponent->GetComponentLocation();
        
        // Rotate Widget to Face Camera
        const FRotator LookRotation = FRotationMatrix::MakeFromX(ToCamera).Rotator();
        StatsWidgetComponent->SetWorldRotation(LookRotation);

        //==========================================================================
        // DISTANCE-BASED FADING
        //==========================================================================
        const float Distance = FVector::Dist(CameraLocation, GetActorLocation());
        float TargetOpacity = 1.0f;

        // Calculate Fade Opacity Based on Distance
        if (Distance > WidgetFadeStartDistance)
        {
            const float Alpha = FMath::Clamp(
                1.0f - (Distance - WidgetFadeStartDistance) / (WidgetFadeEndDistance - WidgetFadeStartDistance),
                0.0f,
                1.0f
            );
            TargetOpacity = Alpha;
        }

        // Apply Smooth Fade Interpolation
        if (UUserWidget* Widget = Cast<UUserWidget>(StatsWidgetComponent->GetUserWidgetObject()))
        {
            float CurrentOpacity = Widget->GetRenderOpacity();
            float NewOpacity = FMath::FInterpTo(CurrentOpacity, TargetOpacity, DeltaTime, WidgetFadeSpeed);
            Widget->SetRenderOpacity(NewOpacity);

            // Update Widget Visibility Based on Opacity
            bool bShouldBeVisible = NewOpacity > 0.01f;
            StatsWidgetComponent->SetVisibility(bShouldBeVisible);
        }
    }
}

//==========================================================================
// DAMAGE SYSTEM
//==========================================================================
float AEnemyCharacter::TakeDamage(
    float DamageAmount,
    FDamageEvent const& DamageEvent,
    AController* EventInstigator,
    AActor* DamageCauser
)
{
    // Early exit if already dead, no damage, or no stats component
    if (bIsDead || DamageAmount <= 0.f || !StatsComponent)
    {
        return 0.f;
    }

    // Call parent implementation first
    const float SuperDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    const float FinalDamage = SuperDamage > 0.f ? SuperDamage : DamageAmount;

    // Apply damage to stats component
    if (FinalDamage > 0.f)
    {
        StatsComponent->TakeDamage(FinalDamage, EventInstigator);
    }

    return FinalDamage;
}

//==========================================================================
// STATS EVENT HANDLERS
//==========================================================================
void AEnemyCharacter::OnHealthChanged(float NewHealth, float Delta)
{
    UE_LOG(LogTemp, Log, TEXT("Enemy %s HP: %f (%+f)"), *GetName(), NewHealth, Delta);
}

void AEnemyCharacter::OnDeath(AActor* DeadActor)
{
    if (bIsDead) return;
    bIsDead = true;

    UE_LOG(LogTemp, Warning, TEXT("Enemy %s died"), *GetName());

    //==========================================================================
    // DEATH SEQUENCE
    //==========================================================================
    
    // Disable Movement
    if (UCharacterMovementComponent* Move = GetCharacterMovement())
    {
        Move->DisableMovement();
        Move->StopMovementImmediately();
    }

    // Stop AI Controller
    if (AAIController* AICont = Cast<AAIController>(GetController()))
    {
        AICont->StopMovement();
    }

    // Enable Ragdoll Physics
    if (USkeletalMeshComponent* MeshComp = GetMesh())
    {
        MeshComp->SetSimulatePhysics(true);
        MeshComp->SetCollisionProfileName(FName("Ragdoll"));
    }

    // Disable Capsule Collision
    if (UCapsuleComponent* Capsule = GetCapsuleComponent())
    {
        Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

    // Auto-destroy after delay
    SetLifeSpan(10.f);
}

//==========================================================================
// STATS ACCESSORS
//==========================================================================
float AEnemyCharacter::GetHealthPercent() const
{
    return StatsComponent ? StatsComponent->GetHealthPercentage() : 0.f;
}