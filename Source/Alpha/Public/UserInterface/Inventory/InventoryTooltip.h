#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryTooltip.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UTextBlock;
class UItemBase;
class UInventoryItemSlot;

//==========================================================================
// CLASS: UInventoryTooltip
//==========================================================================
UCLASS()
class ALPHA_API UInventoryTooltip : public UUserWidget
{
    GENERATED_BODY()

public:
    //==========================================================================
    // PROPERTIES
    //==========================================================================
    
    // Reference to the inventory slot being hovered
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UInventoryItemSlot> InventorySlotBeingHovered;

    // Widget Bindings
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ItemName;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ItemType;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> DamageValue;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> RestorationAmount;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> UsageText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ItemDescription;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> MaxStackSize;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> StackWeight;

protected:
    //==========================================================================
    // PROTECTED FUNCTIONS
    //==========================================================================
    virtual void NativeConstruct() override;
};