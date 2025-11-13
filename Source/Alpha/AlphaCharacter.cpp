//==========================================================================
// INCLUDES
//==========================================================================
// Engine
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/ProgressBar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/AttackComponent.h"

// Game
#include "AlphaCharacter.h"
#include "UserInterface/AlphaHUD.h"
#include "UserInterface/Interaction/InteractionWidget.h"
#include "Components/InventoryComponent.h"
#include "AlphaPlayerController.h"
#include "Interfaces/InteractionInterface.h"
#include "World/LootContainer.h"
#include "World/Pickup.h"

//==========================================================================
// LOG CATEGORY
//==========================================================================
DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//==========================================================================
// CONSTRUCTOR
//==========================================================================
AAlphaCharacter::AAlphaCharacter() :
    InteractionCheckFrequency(0.1f),
    AimingInteractionDistance(0.0f),
    DefaultInteractionDistance(125.0f)
{
    //==========================================================================
    // UNREAL DEFAULT CONSTRUCTION
    //==========================================================================
    
    // Collision Capsule Setup
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Rotation Configuration
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Character Movement Configuration
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 500.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

    // Camera Boom Setup
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // Follow Camera Setup
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    //==========================================================================
    // ALPHA GAME SYSTEMS CONSTRUCTION
    //==========================================================================
    
    // Inventory System
    PlayerInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("PlayerInventory"));
    PlayerInventory->SetSlotsCapacity(20);
    PlayerInventory->SetWeightCapacity(50.0f);

    // Camera Aiming System
    AimingCameraTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("AimingCameraTimeline"));
    DefaultCameraLocation = FVector{0.0f, 0.0f, 65.0f};
    AimingCameraLocation = FVector{150.0f, 100.0f, 65.0f};
    CameraBoom->SocketOffset = DefaultCameraLocation;

    // Character Configuration
    GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
    BaseEyeHeight = 76.0f;
    
    // Stats System
    StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));

    // Combat System
    AttackComp = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));
}

//==========================================================================
// INPUT SYSTEM
//==========================================================================
void AAlphaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        //==========================================================================
        // UNREAL DEFAULT INPUT BINDINGS
        //==========================================================================
        
        // Jumping
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        // Movement
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAlphaCharacter::Move);
        EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AAlphaCharacter::Look);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAlphaCharacter::Look);

        //==========================================================================
        // ALPHA GAME INPUT BINDINGS
        //==========================================================================
        
        // Interaction System
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AAlphaCharacter::BeginInteract);
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &AAlphaCharacter::EndInteract);

        // Aiming System
        EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AAlphaCharacter::Aim);
        EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AAlphaCharacter::StopAiming);

        // UI & Actions
        EnhancedInputComponent->BindAction(ToggleMenuAction, ETriggerEvent::Started, this, &AAlphaCharacter::ToggleMenu);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AAlphaCharacter::StartSprinting);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AAlphaCharacter::StopSprinting);
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AAlphaCharacter::OnAttackPressed);
    }
    else
    {
        UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
    }
}

//==========================================================================
// GAME FLOW
//==========================================================================
void AAlphaCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Initialize Controllers and HUD
    MainPlayerController = Cast<AAlphaPlayerController>(GetController());
    HUD = Cast<AAlphaHUD>(MainPlayerController->GetHUD());

    //==========================================================================
    // CAMERA AIMING TIMELINE SETUP
    //==========================================================================
    FOnTimelineFloat AimLerpAlphaValue;
    FOnTimelineEvent TimelineFinishedEvent;
    AimLerpAlphaValue.BindUFunction(this, FName("UpdateCameraTimeline"));
    TimelineFinishedEvent.BindUFunction(this, FName("CameraTimelineEnd"));

    if (AimingCameraTimeline && AimingCameraCurve)
    {
        AimingCameraTimeline->AddInterpFloat(AimingCameraCurve, AimLerpAlphaValue);
        AimingCameraTimeline->SetTimelineFinishedFunc(TimelineFinishedEvent);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AimingCameraTimeline or AimingCameraCurve were null! Aiming functionality will not work until corrected."));
    }

    //==========================================================================
    // INTERACTION SYSTEM SETUP
    //==========================================================================
    GetWorldTimerManager().SetTimer(
        TH_InteractionCheck,
        this,
        &AAlphaCharacter::PerformInteractionCheck,
        InteractionCheckFrequency,
        true);

    InteractionCollisionQueryParams.bTraceComplex = false;
    InteractionObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel1);

    //==========================================================================
    // UI & STATS SYSTEM SETUP
    //==========================================================================
    CreateStatsWidget();

    if (StatsComponent)
    {
        StatsComponent->OnDeath.AddDynamic(this, &AAlphaCharacter::HandleDeath);
        StatsComponent->OnHealthChanged.AddDynamic(this, &AAlphaCharacter::HandleHealthChanged);
        StatsComponent->OnStaminaChanged.AddDynamic(this, &AAlphaCharacter::HandleStaminaChanged);
        StatsComponent->OnStaminaExhausted.AddDynamic(this, &AAlphaCharacter::StopSprinting);
    }
}

void AAlphaCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    //==========================================================================
    // TIMED INTERACTION PROGRESS UPDATE
    //==========================================================================
    if (GetWorldTimerManager().IsTimerActive(TH_TimedInteraction))
    {
        const float InteractProgress =
            GetWorldTimerManager().GetTimerElapsed(TH_TimedInteraction) /
            InteractionTarget->InteractableData.InteractionDuration;
        HUD->GetInteractionWidget()->InteractionProgressBar->SetPercent(FMath::Clamp(InteractProgress, 0.0f, 1.0f));
    }

    //==========================================================================
    // SPRINT AUTO-MANAGEMENT
    //==========================================================================
    if (StatsComponent && StatsComponent->bIsSprinting && !StatsComponent->CanSprint())
    {
        StopSprinting();
    }
    
    //==========================================================================
    // CONTAINER AUTO-CLOSE CHECK
    //==========================================================================
    if (HUD && HUD->bContainerInterfaceOpen)
    {
        if (const AContainer* OpenContainer = HUD->GetCurrentContainer())
        {
            const float DistSq = FVector::DistSquared(GetActorLocation(), OpenContainer->GetActorLocation());
            
            if (const float MaxDistSq = FMath::Square(ContainerAutoCloseDistance); DistSq > MaxDistSq)
            {
                HUD->HideContainerInterface(false);
                UE_LOG(LogTemp, Log, TEXT("Auto-close container UI: player moved too far from %s"), *OpenContainer->GetName());
            }
        }
    }
}

//==========================================================================
// INTERACTION SYSTEM
//==========================================================================
void AAlphaCharacter::PerformInteractionCheck()
{
    if (FVector::DotProduct(GetActorForwardVector(), GetViewRotation().Vector()) > 0)
    {
        const FVector TraceStart{FollowCamera->GetComponentLocation() + GetViewRotation().Vector() * CameraBoom->TargetArmLength};
        const float InteractionCheckDistance = bAiming ? AimingInteractionDistance : DefaultInteractionDistance;
        const FVector TraceEnd{TraceStart + GetViewRotation().Vector() * InteractionCheckDistance};

        // Debug Visualization
        //DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 2.0f);
        DrawDebugSphere(GetWorld(), TraceEnd, .0f, 8, FColor::Blue, false, 5.0f);

        if (GetWorld()->SweepMultiByObjectType(OutHits, TraceStart, TraceEnd, FQuat::Identity,
            InteractionObjectQueryParams, FCollisionShape::MakeSphere(50.0f), InteractionCollisionQueryParams))
        {
            FHitResult ClosestHit;
            ClosestHit.Distance = FLT_MAX;
            
            // Find closest hit
            for (const FHitResult& Hit : OutHits)
            {
                if (Hit.Distance < ClosestHit.Distance)
                {
                    ClosestHit = Hit;
                }
            }

            // Check for interactable interface
            if (ClosestHit.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
            {
                if (ClosestHit.GetActor() != InteractionTarget.GetObject())
                {
                    // End focus on previous interactable
                    if (IsValid(InteractionTarget.GetObject()))
                    {
                        InteractionTarget->EndFocus();
                    }

                    // Process new interactable
                    FoundInteractable(ClosestHit.GetActor());
                    return;
                }

                // Show interaction widget if container interface was closed
                if (!HUD->bContainerInterfaceOpen && !HUD->bInteractionWidgetVisible)
                {
                    HUD->ShowInteractionWidget();
                }

                return;
            }
        }
    }

    NoInteractableFound();
}

void AAlphaCharacter::FoundInteractable(AActor* NewInteractable)
{
    InteractionTarget = NewInteractable;
    InteractionTarget->BeginFocus();
    HUD->UpdateInteractionWidget(&InteractionTarget->InteractableData);
}

void AAlphaCharacter::NoInteractableFound()
{
    GetWorldTimerManager().ClearTimer(TH_TimedInteraction);

    if (IsValid(InteractionTarget.GetObject()))
    {
        InteractionTarget->EndInteract();
        InteractionTarget->EndFocus();
        InteractionTarget = nullptr;
    }

    HUD->GetInteractionWidget()->InteractionProgressBar->SetPercent(0.0f);
    HUD->HideInteractionWidget();
}

void AAlphaCharacter::BeginInteract()
{
    if (IsValid(InteractionTarget.GetObject()))
    {
        InteractionTarget->BeginInteract();

        if (FMath::IsNearlyZero(InteractionTarget->InteractableData.InteractionDuration, 0.1f))
        {
            Interact();
        }
        else
        {
            GetWorldTimerManager().SetTimer(TH_TimedInteraction, this, &AAlphaCharacter::Interact,
                InteractionTarget->InteractableData.InteractionDuration, false);
        }
    }
}

void AAlphaCharacter::EndInteract()
{
    GetWorldTimerManager().ClearTimer(TH_TimedInteraction);

    if (IsValid(InteractionTarget.GetObject()))
    {
        InteractionTarget->EndInteract();
    }
}

void AAlphaCharacter::Interact()
{
    GetWorldTimerManager().ClearTimer(TH_TimedInteraction);

    if (IsValid(InteractionTarget.GetObject()))
    {
        switch (InteractionTarget->InteractableData.InteractableType)
        {
        case EInteractableType::Pickup:
            break;
        case EInteractableType::NonPlayerCharacter:
            break;
        case EInteractableType::Device:
            break;
        case EInteractableType::Toggle:
            break;
        case EInteractableType::Container:
            if (HUD)
            {
                if (AContainer* Container = Cast<AContainer>(InteractionTarget.GetObject()))
                {
                    if (HUD->bContainerInterfaceOpen && HUD->GetCurrentContainer() == Container)
                    {
                        HUD->HideContainerInterface(false);
                    }
                    else
                    {
                        HUD->ShowContainerInterface(Container);
                    }
                }
            }
            break;
        default:
            break;
        }

        InteractionTarget->Interact(this);
    }
}

void AAlphaCharacter::UpdateInteractionWidget() const
{
    if (IsValid(InteractionTarget.GetObject()))
    {
        HUD->UpdateInteractionWidget(&InteractionTarget->InteractableData);
    }
}

//==========================================================================
// UI SYSTEM
//==========================================================================
void AAlphaCharacter::ToggleMenu()
{
    HUD->ToggleMenu();

    if (HUD->bMainMenuOpen)
    {
        StopAiming();
    }
}

void AAlphaCharacter::CreateStatsWidget()
{
    if (StatsWidgetClass && MainPlayerController)
    {
        StatsWidget = CreateWidget<UStatsWidget>(MainPlayerController, StatsWidgetClass);
        if (StatsWidget && StatsComponent)
        {
            StatsWidget->InitializeWidget(StatsComponent);
            StatsWidget->AddToViewport();
        }
    }
}

//==========================================================================
// AIMING SYSTEM
//==========================================================================
void AAlphaCharacter::Aim()
{
    if (!HUD->HasAnyMenuOpen())
    {
        // Stop sprinting when aiming
        if (StatsComponent && StatsComponent->bIsSprinting)
        {
            StopSprinting();
        }
        
        bAiming = true;
        bUseControllerRotationYaw = true;
        GetCharacterMovement()->MaxWalkSpeed = 400.0f;

        if (AimingCameraTimeline)
        {
            AimingCameraTimeline->PlayFromStart();
        }
    }
}

void AAlphaCharacter::StopAiming()
{
    if (bAiming)
    {
        bAiming = false;
        bUseControllerRotationYaw = false;
        HUD->HideCrosshair();
        GetCharacterMovement()->MaxWalkSpeed = 500.f;

        if (AimingCameraTimeline)
        {
            AimingCameraTimeline->Reverse();
        }
    }
}

void AAlphaCharacter::UpdateCameraTimeline(const float TimelineValue) const
{
    const FVector CameraLocation = FMath::Lerp(DefaultCameraLocation, AimingCameraLocation, TimelineValue);
    CameraBoom->SocketOffset = CameraLocation;
}

void AAlphaCharacter::CameraTimelineEnd() const
{
    if (AimingCameraTimeline)
    {
        if (AimingCameraTimeline->GetPlaybackPosition() != 0.0f)
        {
            HUD->ShowCrosshair();
        }
    }
}

//==========================================================================
// MOVEMENT SYSTEM
//==========================================================================
void AAlphaCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();
    DoMove(MovementVector.X, MovementVector.Y);
}

void AAlphaCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();
    DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AAlphaCharacter::DoMove(const float Right, const float Forward)
{
    if (GetController() != nullptr)
    {
        const FRotator Rotation = GetController()->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, Forward);
        AddMovementInput(RightDirection, Right);
    }
}

void AAlphaCharacter::DoLook(float Yaw, float Pitch)
{
    if (GetController() != nullptr)
    {
        AddControllerYawInput(Yaw);
        AddControllerPitchInput(Pitch);
    }
}

void AAlphaCharacter::DoJumpStart()
{
    Jump();
}

void AAlphaCharacter::DoJumpEnd()
{
    StopJumping();
}

//==========================================================================
// SPRINT SYSTEM
//==========================================================================
void AAlphaCharacter::StartSprinting()
{
    if (StatsComponent && StatsComponent->CanSprint() && !bAiming)
    {
        StatsComponent->StartSprinting();
        
        UCharacterMovementComponent* MovementComp = GetCharacterMovement();
        if (MovementComp)
        {
            MovementComp->MaxWalkSpeed = 600.0f;
        }
    }
}

void AAlphaCharacter::StopSprinting()
{
    if (StatsComponent)
    {
        StatsComponent->StopSprinting();
        
        UCharacterMovementComponent* MovementComp = GetCharacterMovement();
        if (MovementComp)
        {
            MovementComp->MaxWalkSpeed = 500.0f;
        }
    }
}

//==========================================================================
// COMBAT SYSTEM
//==========================================================================
void AAlphaCharacter::OnAttackPressed()
{
    if (AttackComp)
    {
        AttackComp->OnAttackInput();
    }
}

//==========================================================================
// INVENTORY SYSTEM
//==========================================================================
void AAlphaCharacter::DropItem(UItemBase* ItemToDrop)
{
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.bNoFail = true;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    const FVector SpawnLocation{GetActorLocation() + GetActorForwardVector() * 50.0f};
    const FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

    APickup* Pickup = GetWorld()->SpawnActor<APickup>(APickup::StaticClass(), SpawnTransform, SpawnParams);
    Pickup->InitializeDrop(ItemToDrop);
    PlayerInventory->HandleRemoveItem(ItemToDrop);
}

//==========================================================================
// LOOT SYSTEM
//==========================================================================
void AAlphaCharacter::NotifyLootPickedUp(const FInteractableData& LootData) const
{
    OnLootPickedUp.Broadcast(LootData);
}

void AAlphaCharacter::ExitContainerRadius() const
{
    HUD->ClearTargetContainer();
}

//==========================================================================
// STATS SYSTEM EVENT HANDLERS
//==========================================================================
void AAlphaCharacter::HandleDeath(AActor* DeadActor)
{
    UE_LOG(LogTemp, Warning, TEXT("Character died!"));
    
    if (MainPlayerController)
    {
        DisableInput(MainPlayerController);
    }
}

void AAlphaCharacter::HandleHealthChanged(const float NewHealth, float Delta)
{
    UE_LOG(LogTemp, Log, TEXT("Health changed: %.1f (Delta: %.1f)"), NewHealth, Delta);
}

void AAlphaCharacter::HandleStaminaChanged(const float NewStamina, const float Delta)
{
    UE_LOG(LogTemp, Log, TEXT("Stamina changed: %.1f (Delta: %.1f)"), NewStamina, Delta);
}