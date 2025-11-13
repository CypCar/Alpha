#include "UserInterface/Inventory/InventoryTooltip.h"
#include "Components/TextBlock.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "Items/ItemBase.h"

//==========================================================================
// NATIVE CONSTRUCT
//==========================================================================
void UInventoryTooltip::NativeConstruct()
{
    Super::NativeConstruct();

    if (const UItemBase* ItemBeingHovered = InventorySlotBeingHovered->InternalItemReference)
    {
        //==========================================================================
        // ITEM QUALITY COLOR CODING
        //==========================================================================
        switch (ItemBeingHovered->ItemQuality)
        {
        case EItemQuality::Shoddy:
            ItemType->SetColorAndOpacity(FLinearColor::Gray);
            break;
        case EItemQuality::Common:
            ItemType->SetColorAndOpacity(FLinearColor::White);
            break;
        case EItemQuality::Quality:
            ItemType->SetColorAndOpacity(FLinearColor(0.0f, 0.51f, 0.169f));
            break;
        case EItemQuality::Masterwork:
            ItemType->SetColorAndOpacity(FLinearColor(0.0f, 0.4f, 0.75f));
            break;
        case EItemQuality::Grandmaster:
            ItemType->SetColorAndOpacity(FLinearColor(1.0f, 0.45f, 0.0f));
            break;
        default:
            break;
        }

        //==========================================================================
        // ITEM TYPE SPECIFIC DISPLAY
        //==========================================================================
        switch (ItemBeingHovered->ItemType)
        {
        case EItemType::Armor:
            // Future implementation for armor tooltips
            break;

        case EItemType::Weapon:
            // Future implementation for weapon tooltips
            break;

        case EItemType::Shield:
            // Future implementation for shield tooltips
            break;

        case EItemType::Spell:
            // Future implementation for spell tooltips
            break;

        case EItemType::Consumable:
            ItemType->SetText(FText::FromString("Consumable"));
            DamageValue->SetVisibility(ESlateVisibility::Collapsed);
            break;

        case EItemType::Quest:
            // Future implementation for quest item tooltips
            break;

        case EItemType::Mundane:
            ItemType->SetText(FText::FromString("Mundane"));
            DamageValue->SetVisibility(ESlateVisibility::Collapsed);
            RestorationAmount->SetVisibility(ESlateVisibility::Collapsed);
            UsageText->SetVisibility(ESlateVisibility::Collapsed);
            break;

        default:
            break;
        }

        //==========================================================================
        // BASIC ITEM INFORMATION
        //==========================================================================
        ItemName->SetText(ItemBeingHovered->TextData.Name);
        DamageValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.DamageValue));
        UsageText->SetText(ItemBeingHovered->TextData.UsageText);
        ItemDescription->SetText(ItemBeingHovered->TextData.Description);

        //==========================================================================
        // RESTORATION INFORMATION
        //==========================================================================
        const FString RestorationInfo = 
            "Restoration: " + FString::SanitizeFloat(ItemBeingHovered->ItemStatistics.RestorationAmount);
        RestorationAmount->SetText(FText::FromString(RestorationInfo));

        //==========================================================================
        // WEIGHT INFORMATION
        //==========================================================================
        const FString WeightInfo = 
            "Weight: " + FString::SanitizeFloat(ItemBeingHovered->GetItemStackWeight());
        StackWeight->SetText(FText::FromString(WeightInfo));

        //==========================================================================
        // STACK INFORMATION
        //==========================================================================
        if (ItemBeingHovered->NumericData.bIsStackable)
        {
            const FString StackInfo = 
                "Max stack size: " + FString::FromInt(ItemBeingHovered->NumericData.MaxStackSize);
            MaxStackSize->SetText(FText::FromString(StackInfo));
        }
        else
        {
            MaxStackSize->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}