//==========================================================================
// INCLUDES
//==========================================================================
// Game
#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "UserInterface/Inventory/InventoryTooltip.h"
#include "UserInterface/Inventory/DragItemVisual.h"
#include "UserInterface/Inventory/ItemDragDropOperation.h"
#include "UserInterface/Inventory/InventorySubmenu.h"
#include "UserInterface/Inventory/InventoryPanel.h"
#include "Items/ItemBase.h"

// Engine
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

//==========================================================================
// WIDGET INITIALIZATION
//==========================================================================
void UInventoryItemSlot::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    // Create and configure tooltip widget
    if (ToolTipClass)
    {
        UInventoryTooltip* ToolTip = CreateWidget<UInventoryTooltip>(this, ToolTipClass);
        ToolTip->InventorySlotBeingHovered = this;
        SetToolTip(ToolTip);
    }
}

void UInventoryItemSlot::NativeConstruct()
{
    Super::NativeConstruct();

    if (InternalItemReference)
    {
        //==========================================================================
        // ITEM QUALITY VISUALIZATION
        //==========================================================================
        switch (InternalItemReference->ItemQuality)
        {
        case EItemQuality::Shoddy:
            ItemBorder->SetBrushColor(FLinearColor::Gray);
            break;
        case EItemQuality::Common:
            ItemBorder->SetBrushColor(FLinearColor::White);
            break;
        case EItemQuality::Quality:
            ItemBorder->SetBrushColor(FLinearColor(0.0f, 0.51f, 0.169f));
            break;
        case EItemQuality::Masterwork:
            ItemBorder->SetBrushColor(FLinearColor(0.0f, 0.4f, 0.75f));
            break;
        case EItemQuality::Grandmaster:
            ItemBorder->SetBrushColor(FLinearColor(1.0f, 0.45f, 0.0f));
            break;
        default:
            break;
        }

        //==========================================================================
        // ITEM VISUAL SETUP
        //==========================================================================
        ItemIcon->SetBrushFromTexture(InternalItemReference->AssetData.Icon);

        //==========================================================================
        // QUANTITY DISPLAY
        //==========================================================================
        if (InternalItemReference->NumericData.bIsStackable)
        {
            ItemQuantity->SetText(FText::AsNumber(InternalItemReference->Quantity));
        }
        else
        {
            ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

//==========================================================================
// MOUSE INTERACTION
//==========================================================================
FReply UInventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    //==========================================================================
    // LEFT CLICK - DRAG DETECTION
    //==========================================================================
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
    }

    //==========================================================================
    // RIGHT CLICK - CONTEXT MENU
    //==========================================================================
    if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
    {
        if (IsValid(SubMenuReference))
        {
            // Position submenu at mouse cursor
            float MouseX, MouseY;
            if (!GetOwningPlayer()->GetMousePosition(MouseX, MouseY))
            {
                UE_LOG(LogTemp, Error, TEXT("%s: GetOwningPlayer()->GetMousePosition() returned false!"),
                    *FString(__FUNCTION__));
            }
            
            const FVector2D WidgetPosition{MouseX, MouseY};
            SubMenuReference->SetPositionInViewport(WidgetPosition);

            // Spawn the submenu slightly to the left and above the mouse pointer
            // for easier mouse movement into the menu
            SubMenuReference->SetAlignmentInViewport(FVector2D{0.05, 0.05});
            SubMenuReference->SelectedItem = InternalItemReference;

            // Show or update submenu
            if (!SubMenuReference->bSubMenuActive)
            {
                SubMenuReference->OriginatingItemSlot = this;
                SubMenuReference->HideSubmenuWidgets();
                SubMenuReference->SetVisibility(ESlateVisibility::Visible);
            }
            else if (SubMenuReference->bSubMenuActive)
            {
                // If submenu is already active, link it to the new item slot data
                SubMenuReference->OriginatingItemSlot = this;
                SubMenuReference->HideSubmenuWidgets();
            }

            // Configure submenu buttons for the current item
            SubMenuReference->ConfigureSubmenuButtons();

            return Reply.Handled();
        }

        return Reply.Unhandled();
    }

    return Reply.Unhandled();
}

void UInventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);
}

//==========================================================================
// DRAG AND DROP SYSTEM
//==========================================================================
void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                              UDragDropOperation*& OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

    if (DragItemVisualClass)
    {
        //==========================================================================
        // CREATE DRAG VISUAL WIDGET
        //==========================================================================
        const TObjectPtr<UDragItemVisual> DragVisual = CreateWidget<UDragItemVisual>(this, DragItemVisualClass);
        DragVisual->ItemIcon->SetBrushFromTexture(InternalItemReference->AssetData.Icon);
        DragVisual->ItemBorder->SetBrushColor(ItemBorder->GetBrushColor());

        //==========================================================================
        // CONFIGURE QUANTITY DISPLAY FOR DRAG VISUAL
        //==========================================================================
        if (InternalItemReference->NumericData.bIsStackable)
        {
            DragVisual->ItemQuantity->SetText(FText::AsNumber(InternalItemReference->Quantity));
        }
        else
        {
            DragVisual->ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);
        }

        //==========================================================================
        // CREATE DRAG DROP OPERATION
        //==========================================================================
        UItemDragDropOperation* DragItemOperation = NewObject<UItemDragDropOperation>();
        DragItemOperation->SourceItem = InternalItemReference;
        DragItemOperation->DefaultDragVisual = DragVisual;
        DragItemOperation->Pivot = EDragPivot::TopLeft;

        OutOperation = DragItemOperation;
    }
}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                      UDragDropOperation* InOperation)
{
    const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);

    // Only handle if not dropping the item on itself
    if (ItemDragDrop->SourceItem != InternalItemReference)
    {
        // Only take action if the same kind of item is being dropped onto this slot
        if (ItemDragDrop->SourceItem->ID == InternalItemReference->ID)
        {
            // Perform stack merge operation
            OwningInventoryPanel->InventoryReference->MergeItems(InternalItemReference, ItemDragDrop->SourceItem);
            return true;
        }
    }

    return false;
}