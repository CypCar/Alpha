// TestDummyCharacter.cpp
#include "World/NPC/TestDummyCharacter.h"   
#include "Components/StatsComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/HUD/StatsWidget.h"

//==========================================================================
// CONSTRUCTOR
//==========================================================================
ATestDummyCharacter::ATestDummyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Stats Component Setup
    StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));

    // Widget Component Setup
    StatsWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatsWidgetComponent"));
    StatsWidgetComponent->SetupAttachment(RootComponent);

    StatsWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
    StatsWidgetComponent->SetDrawAtDesiredSize(true);
    StatsWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
    StatsWidgetComponent->SetWidgetClass(UStatsWidget::StaticClass());
}

//==========================================================================
// GAME FLOW
//==========================================================================
void ATestDummyCharacter::BeginPlay()
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
        StatsComponent->OnHealthChanged.AddDynamic(this, &ATestDummyCharacter::OnHealthChanged);
        StatsComponent->OnDeath.AddDynamic(this, &ATestDummyCharacter::OnDeath);
    }
}

void ATestDummyCharacter::Tick(float DeltaTime)
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
float ATestDummyCharacter::TakeDamage(
    float DamageAmount,
    FDamageEvent const& DamageEvent,
    AController* EventInstigator,
    AActor* DamageCauser
)
{
    // Call parent implementation first
    const float SuperDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    const float FinalDamage = SuperDamage > 0.f ? SuperDamage : DamageAmount;

    // Apply damage to stats component
    if (StatsComponent && FinalDamage > 0.f)
    {
        StatsComponent->TakeDamage(FinalDamage, EventInstigator);
    }

    return FinalDamage;
}

//==========================================================================
// STATS EVENT HANDLERS
//==========================================================================
void ATestDummyCharacter::OnHealthChanged(const float NewHealth, const float Delta)
{
    UE_LOG(LogTemp, Log, TEXT("Dummy HP: %f (%+f)"), NewHealth, Delta);
}

void ATestDummyCharacter::OnDeath(AActor* DeadActor)
{
    UE_LOG(LogTemp, Warning, TEXT("Dummy died: %s"), *GetName());

    //==========================================================================
    // RAGDOLL SYSTEM
    //==========================================================================
    if (USkeletalMeshComponent* MeshComp = GetMesh())
    {
        MeshComp->SetSimulatePhysics(true);
        MeshComp->SetCollisionProfileName(FName("Ragdoll"));
    }

    // Disable collision on capsule component
    if (UCapsuleComponent* Capsule = GetCapsuleComponent())
    {
        Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

    // Auto-destroy after delay
    SetLifeSpan(10.f);
}