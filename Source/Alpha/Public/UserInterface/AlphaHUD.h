#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AlphaHUD.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class ULootWindowWidget;
class UMainMenu;
class UInteractionWidget;
class UAmountWidget;
class AContainer;
class UContainerInterface;
class AAlphaCharacter;
struct FInteractableData;

//==========================================================================
// CLASS: AAlphaHUD
//==========================================================================
UCLASS()
class ALPHA_API AAlphaHUD : public AHUD
{
    GENERATED_BODY()

public:
    //==========================================================================
    // CONSTRUCTOR & PUBLIC FUNCTIONS
    //==========================================================================
    AAlphaHUD();

    // Menu System
    bool HasAnyMenuOpen() const;
    void DisplayMenu();
    void HideMenu();
    void ToggleMenu();

    // Crosshair System
    void ShowCrosshair() const;
    void HideCrosshair() const;

    // Interaction System
    void ShowInteractionWidget();
    void HideInteractionWidget();
    void UpdateInteractionWidget(const FInteractableData* InteractableData) const;
    TObjectPtr<UInteractionWidget> GetInteractionWidget() { return InteractionWidget; }

    // Container Interface System
    UFUNCTION(BlueprintCallable, Category = "HUD|Container")
    void ShowContainerInterface(AContainer* TargetContainer = nullptr);

    UFUNCTION(BlueprintCallable, Category = "HUD|Container")
    void HideContainerInterface(bool bSuccess = true);

    UFUNCTION(BlueprintCallable, Category = "HUD|Container")
    void SetTargetContainer(AContainer* TargetContainer);
    
    UFUNCTION(BlueprintCallable, Category = "HUD|Container")
    void ClearTargetContainer();

    UFUNCTION(BlueprintPure, Category = "HUD|Container")
    AContainer* GetCurrentContainer() const;

    //==========================================================================
    // PUBLIC PROPERTIES
    //==========================================================================
    UPROPERTY(BlueprintReadOnly, Category = "HUD State")
    bool bMainMenuOpen;

    UPROPERTY(BlueprintReadOnly, Category = "HUD State")
    bool bContainerInterfaceOpen;

    UPROPERTY(BlueprintReadOnly, Category = "HUD State")
    bool bInteractionWidgetVisible;

protected:
    //==========================================================================
    // PROTECTED FUNCTIONS
    //==========================================================================
    virtual void BeginPlay() override;
    void CreateGameWidgets();

    //==========================================================================
    // PROTECTED PROPERTIES
    //==========================================================================
    
    // Widget Classes
    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UMainMenu> MainMenuClass;

    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UInteractionWidget> InteractionWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UUserWidget> CrosshairWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UContainerInterface> ContainerInterfaceClass;
    
    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<ULootWindowWidget> LootWindowWidgetClass;

    // Widget Instances
    UPROPERTY()
    TObjectPtr<UMainMenu> MainMenuWidget;

    UPROPERTY()
    TObjectPtr<UInteractionWidget> InteractionWidget;

    UPROPERTY()
    TObjectPtr<UUserWidget> CrosshairWidget;

    UPROPERTY()
    TObjectPtr<ULootWindowWidget> LootWindowWidget;

private:
    //==========================================================================
    // PRIVATE PROPERTIES
    //==========================================================================
    UPROPERTY()
    TObjectPtr<UContainerInterface> ContainerInterface = nullptr;
    
    UPROPERTY()
    bool bContainerInterfaceManuallyOpened = false;
};