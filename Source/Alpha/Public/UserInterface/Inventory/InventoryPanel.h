#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPanel.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UInventoryItemSlot;
class UInventoryComponent;
class UInventorySubmenu;
class AAlphaCharacter;
class UWrapBox;
class UGridPanel;
class UTextBlock;

//==========================================================================
// CLASS: UInventoryPanel
//==========================================================================
UCLASS()
class ALPHA_API UInventoryPanel : public UUserWidget
{
    GENERATED_BODY()

public:
    //==========================================================================
    // PUBLIC FUNCTIONS
    //==========================================================================
    UFUNCTION()
    void RefreshInventory();

    void LinkToInventory(UInventoryComponent* InputInventory, AAlphaCharacter* InputCharacter = nullptr);
    void UnlinkFromInventory();

    //==========================================================================
    // PUBLIC PROPERTIES
    //==========================================================================
    UPROPERTY(BlueprintReadWrite, Category = "Inventory")
    bool bIsLinkedToInventory;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UWrapBox> InventoryWrapBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> InventoryLabel;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> WeightInfo;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> CapacityInfo;

    UPROPERTY()
    TObjectPtr<UInventoryComponent> InventoryReference;

    UPROPERTY()
    TObjectPtr<UInventorySubmenu> SubMenu;

    // Widget Classes
    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UInventoryItemSlot> InventorySlotClass;

    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UInventorySubmenu> InventorySubMenuClass;

protected:
    //==========================================================================
    // PROTECTED FUNCTIONS
    //==========================================================================
    virtual void NativeOnInitialized() override;
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, 
                             UDragDropOperation* InOperation) override;

    void SetInfoText() const;
};