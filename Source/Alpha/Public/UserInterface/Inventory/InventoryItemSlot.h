#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemSlot.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UInventoryPanel;
class UInventoryTooltip;
class UInventorySubmenu;
class UDragItemVisual;
class UItemBase;
class UTextBlock;
class UBorder;
class UImage;

//==========================================================================
// CLASS: UInventoryItemSlot
//==========================================================================
UCLASS()
class ALPHA_API UInventoryItemSlot : public UUserWidget
{
    GENERATED_BODY()

public:
    //==========================================================================
    // PUBLIC PROPERTIES
    //==========================================================================
    UPROPERTY(VisibleAnywhere, Category = "Inventory Slot")
    TObjectPtr<UItemBase> InternalItemReference;

    UPROPERTY()
    TObjectPtr<UInventorySubmenu> SubMenuReference;

    UPROPERTY()
    TObjectPtr<UInventoryPanel> OwningInventoryPanel;

protected:
    //==========================================================================
    // PROTECTED FUNCTIONS
    //==========================================================================
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, 
                                     UDragDropOperation*& OutOperation) override;
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, 
                             UDragDropOperation* InOperation) override;

    //==========================================================================
    // PROTECTED PROPERTIES
    //==========================================================================
    
    // Widget Bindings
    UPROPERTY(VisibleAnywhere, Category = "Inventory Slot", meta = (BindWidget))
    TObjectPtr<UBorder> ItemBorder;

    UPROPERTY(VisibleAnywhere, Category = "Inventory Slot", meta = (BindWidget))
    TObjectPtr<UImage> ItemIcon;

    UPROPERTY(VisibleAnywhere, Category = "Inventory Slot", meta = (BindWidget))
    TObjectPtr<UTextBlock> ItemQuantity;

    // Widget Classes
    UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot")
    TSubclassOf<UDragItemVisual> DragItemVisualClass;

    UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot")
    TSubclassOf<UInventoryTooltip> ToolTipClass;
};