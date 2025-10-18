// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "UserInterface/Inventory/InventoryTooltip.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Items/ItemBase.h"

void UInventoryItemSlot::NativeOnInitialized()
{
    Super::NativeOnInitialized();
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

    if (ItemReference)
    {
        switch (ItemReference->ItemQuality)
        {
        case EItemQuality::Shoddy:
            ItemBorder->SetBrushColor(FLinearColor::Gray);
            break;
        case EItemQuality::Common: 
            ItemBorder->SetBrushColor(FLinearColor::White);
            break;
        case EItemQuality::Quality: 
            ItemBorder->SetBrushColor(FLinearColor::Green);
            break;
        case EItemQuality::Masterwork: 
            ItemBorder->SetBrushColor(FLinearColor::Blue);
            break;
        case EItemQuality::Grandmaster: 
            ItemBorder->SetBrushColor(FLinearColor(100.0f,65.0f,0.0f,1.0f));//orange
            break;
        default:;
        }
        ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);

        if (ItemReference->NumericData.bIsStackable)
        {
            ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));
        }
        else
        {
            ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

/*FReply UInventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
    return ;
}*/

void UInventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);
}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& InOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, InOperation);
}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

}
