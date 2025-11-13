#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySubmenu.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UItemBase;
class AAlphaCharacter;
class UInventoryComponent;
class UInventoryItemSlot;
class UAmountWidget;
class UButton;

//==========================================================================
// CLASS: UInventorySubmenu
//==========================================================================
UCLASS()
class ALPHA_API UInventorySubmenu : public UUserWidget
{
    GENERATED_BODY()

public:
    //==========================================================================
    // PUBLIC FUNCTIONS
    //==========================================================================
    FORCEINLINE bool SplitIsInProgress() const { return bSplitInProgress; }

    void HideSubmenuWidgets() const;
    void ConfigureSubmenuButtons();

    //==========================================================================
    // PUBLIC PROPERTIES
    //==========================================================================
    UPROPERTY()
    TObjectPtr<UInventoryComponent> LinkedInventory;

    UPROPERTY()
    TObjectPtr<UInventoryItemSlot> OriginatingItemSlot;

    UPROPERTY()
    TObjectPtr<AAlphaCharacter> PlayerCharacter;

    UPROPERTY(BlueprintReadOnly, Category = "Inventory")
    TObjectPtr<UItemBase> SelectedItem;

    UPROPERTY(BlueprintReadOnly)
    bool bSubMenuActive;

protected:
    //==========================================================================
    // PROTECTED FUNCTIONS
    //==========================================================================
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

    // Button Handlers
    UFUNCTION()
    void UseButtonClicked();

    UFUNCTION()
    void DropButtonClicked();

    UFUNCTION()
    void SplitButtonClicked();

    UFUNCTION()
    void SplitConfirmed(int32 AmountToSplit);

    // Internal Functions
    void CloseSubmenu();

    //==========================================================================
    // PROTECTED PROPERTIES
    //==========================================================================
    
    // State Variables
    UPROPERTY()
    bool bSplitInProgress;

    UPROPERTY()
    bool bItemCanBeSplit;

    // Widget Bindings
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> UseButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> DropButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> SplitButton;

    UPROPERTY()
    TObjectPtr<UAmountWidget> AmountWidget;

    // Configuration
    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    USoundBase* UseSound;

    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UAmountWidget> AmountWidgetClass;
};