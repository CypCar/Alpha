#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
// Engine
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// Game
#include "UserInterface/AlphaHUD.h"
#include "AlphaPlayerController.h"
#include "Interfaces/InteractionInterface.h"
#include "Components/StatsComponent.h"
#include "UserInterface/HUD/StatsWidget.h"
#include "AlphaCharacter.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UAttackComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UTimelineComponent;
class UInventoryComponent;
class UItemBase;
class UInputMappingContext;
struct FInputActionValue;

//==========================================================================
// DELEGATES
//==========================================================================
DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLootPickedUpSignature, const FInteractableData&, LootData);

//==========================================================================
// CLASS: AAlphaCharacter
//==========================================================================
UCLASS(abstract)
class AAlphaCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    //==========================================================================
    // CONSTRUCTOR & PUBLIC FUNCTIONS
    //==========================================================================
    AAlphaCharacter();

    // Unreal Default Functions
    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
    FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TH_TimedInteraction); }
    FORCEINLINE UInventoryComponent* GetInventory() const { return PlayerInventory; }
    FORCEINLINE AAlphaHUD* GetHUD() const { return HUD; }

    // Interaction System
    void UpdateInteractionWidget() const;
    void DropItem(UItemBase* ItemToDrop);
    void ExitContainerRadius() const;
    void NotifyLootPickedUp(const FInteractableData& LootData) const;

    // UI Management
    UFUNCTION(BlueprintCallable, Category = "UI")
    void CreateStatsWidget();

    // Movement System
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void StartSprinting();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void StopSprinting();

    // Combat System
    UFUNCTION(BlueprintCallable, Category = "Action")
    void OnAttackPressed();

    //==========================================================================
    // PUBLIC PROPERTIES
    //==========================================================================
    UPROPERTY(BlueprintReadWrite, Category = "Combat")
    bool bAiming;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStatsComponent* StatsComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UStatsWidget> StatsWidgetClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    UStatsWidget* StatsWidget;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FLootPickedUpSignature OnLootPickedUp;

protected:
    //==========================================================================
    // PROTECTED FUNCTIONS
    //==========================================================================
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    // Input System
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void ToggleMenu();
    void Aim();
    void StopAiming();

    // Camera System
    UFUNCTION()
    void UpdateCameraTimeline(const float TimelineValue) const;

    UFUNCTION()
    void CameraTimelineEnd() const;

    // Interaction System
    void PerformInteractionCheck();
    void FoundInteractable(AActor* NewInteractable);
    void NoInteractableFound();
    void BeginInteract();
    void EndInteract();
    void Interact();

    // Blueprint Callable Input Functions
    UFUNCTION(BlueprintCallable, Category = "PlayerCharacter | Input")
    virtual void DoMove(float Right, float Forward);

    UFUNCTION(BlueprintCallable, Category = "PlayerCharacter | Input")
    virtual void DoLook(float Yaw, float Pitch);

    UFUNCTION(BlueprintCallable, Category = "PlayerCharacter | Input")
    virtual void DoJumpStart();

    UFUNCTION(BlueprintCallable, Category = "PlayerCharacter | Input")
    virtual void DoJumpEnd();

private:
    //==========================================================================
    // PRIVATE FUNCTIONS
    //==========================================================================
    UFUNCTION()
    void HandleDeath(AActor* DeadActor);

    UFUNCTION()
    void HandleHealthChanged(float NewHealth, float Delta);

    UFUNCTION()
    void HandleStaminaChanged(float NewStamina, float Delta);

    //==========================================================================
    // PROTECTED PROPERTIES
    //==========================================================================
    
    // Camera Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;

    // Input Actions - Movement
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter | Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter | Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter | Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter | Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* MouseLookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter | Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* SprintAction;

    // Game Systems
    UPROPERTY()
    TObjectPtr<AAlphaHUD> HUD;

    UPROPERTY()
    TObjectPtr<AAlphaPlayerController> MainPlayerController;

    UPROPERTY(VisibleAnywhere, Category = "PlayerCharacter | Inventory")
    TObjectPtr<UInventoryComponent> PlayerInventory;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    UAttackComponent* AttackComp;

    // Input Mapping
    UPROPERTY(EditAnywhere, Category = "PlayerCharacter | Input")
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    UPROPERTY(EditAnywhere, Category = "PlayerCharacter | Input")
    TObjectPtr<UInputAction> InteractAction;

    UPROPERTY(EditAnywhere, Category = "PlayerCharacter | Input")
    TObjectPtr<UInputAction> AimAction;

    UPROPERTY(EditDefaultsOnly, Category = "PlayerCharacter | Input")
    TObjectPtr<UInputAction> ToggleMenuAction;

    UPROPERTY(EditDefaultsOnly, Category = "PlayerCharacter | Input")
    TObjectPtr<UInputAction> AttackAction;

    // Interaction System
    UPROPERTY(EditAnywhere, Category = "PlayerCharacter | Interaction")
    float InteractionCheckFrequency;

    UPROPERTY(EditAnywhere, Category = "PlayerCharacter | Interaction")
    float AimingInteractionDistance;

    UPROPERTY(EditAnywhere, Category = "PlayerCharacter | Interaction")
    float DefaultInteractionDistance;

    UPROPERTY(VisibleAnywhere, Category = "PlayerCharacter | Interaction")
    TScriptInterface<IInteractionInterface> InteractionTarget;

    UPROPERTY(EditDefaultsOnly, Category = "PlayerCharacter | Interaction")
    float ContainerAutoCloseDistance = 300.f;

    // Camera Aiming System
    UPROPERTY(VisibleAnywhere, Category = "PlayerCharacter | Aiming")
    FVector DefaultCameraLocation;

    UPROPERTY(VisibleAnywhere, Category = "PlayerCharacter | Aiming")
    FVector AimingCameraLocation;

    UPROPERTY(VisibleAnywhere, Category = "PlayerCharacter | Aiming")
    TObjectPtr<UTimelineComponent> AimingCameraTimeline;

    UPROPERTY(EditDefaultsOnly, Category = "PlayerCharacter | Aiming")
    TObjectPtr<UCurveFloat> AimingCameraCurve;

    // Internal Variables
    FCollisionQueryParams InteractionCollisionQueryParams;
    FCollisionObjectQueryParams InteractionObjectQueryParams;
    TArray<FHitResult> OutHits;
    FTimerHandle TH_TimedInteraction;
    FTimerHandle TH_InteractionCheck;
};