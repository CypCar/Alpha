//==========================================================================
// INCLUDES
//==========================================================================
// Game
#include "UserInterface/Inventory/InventorySubMenu.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "UserInterface/Inventory/AmountWidget.h"
#include "Components/InventoryComponent.h"
#include "Alpha/AlphaCharacter.h"
#include "Items/ItemBase.h"

// Engine
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

//==========================================================================
// WIDGET INITIALIZATION
//==========================================================================
void UInventorySubmenu::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    // Initialize Amount Widget
    if (AmountWidgetClass)
    {
        AmountWidget = CreateWidget<UAmountWidget>(this, AmountWidgetClass);
        AmountWidget->AddToViewport(11);
        AmountWidget->SetVisibility(ESlateVisibility::Collapsed);
        AmountWidget->OnValueConfirm.BindUObject(this, &UInventorySubmenu::SplitConfirmed);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s: AmountWidgetClass was null!"), *FString(__FUNCTION__));
    }

    // Bind Button Events
    UseButton->OnClicked.AddDynamic(this, &UInventorySubmenu::UseButtonClicked);
    DropButton->OnClicked.AddDynamic(this, &UInventorySubmenu::DropButtonClicked);
    SplitButton->OnClicked.AddDynamic(this, &UInventorySubmenu::SplitButtonClicked);

    // Initialize State Variables
    bSubMenuActive = false;
    bSplitInProgress = false;
}

void UInventorySubmenu::NativeConstruct()
{
    Super::NativeConstruct();
}

//==========================================================================
// SUBMENU VISIBILITY MANAGEMENT
//==========================================================================
void UInventorySubmenu::HideSubmenuWidgets() const
{
    if (AmountWidget)
    {
        AmountWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UInventorySubmenu::ConfigureSubmenuButtons()
{
    if (OriginatingItemSlot->InternalItemReference->NumericData.bIsStackable &&
        OriginatingItemSlot->InternalItemReference->Quantity > 1)
    {
        SplitButton->SetRenderOpacity(1.0);
        bItemCanBeSplit = true;
    }
    else
    {
        // TODO: Find a better way to visually show the button is disabled
        SplitButton->SetRenderOpacity(0.6);
        bItemCanBeSplit = false;
    }
}

//==========================================================================
// BUTTON HANDLERS
//==========================================================================
void UInventorySubmenu::UseButtonClicked()
{
    if (!SelectedItem || !LinkedInventory || !PlayerCharacter) return;

    const EItemUseResult Result = LinkedInventory->UseItemForActor(SelectedItem, PlayerCharacter);

    switch (Result)
    {
    case EItemUseResult::IUR_Success:
        UE_LOG(LogTemp, Log, TEXT("Used item %s successfully."),
            *SelectedItem->TextData.Name.ToString());
            
        // Play sound for consumable items
        if (PlayerCharacter && SelectedItem->ItemType == EItemType::Consumable)
        {
            UGameplayStatics::PlaySoundAtLocation(
                this,
                UseSound,
                PlayerCharacter->GetActorLocation()
            );
        }
        break;
        
    case EItemUseResult::IUR_WrongType:
        UE_LOG(LogTemp, Warning, TEXT("%s is not a usable (consumable) item."),
            *SelectedItem->TextData.Name.ToString());
        break;
        
    case EItemUseResult::IUR_NoStats:
        UE_LOG(LogTemp, Warning, TEXT("No StatsComponent found on player to apply heal."));
        break;
        
    default:
        UE_LOG(LogTemp, Warning, TEXT("Failed to use item %s."), *SelectedItem->TextData.Name.ToString());
        break;
    }

    SetVisibility(ESlateVisibility::Collapsed);
}

void UInventorySubmenu::DropButtonClicked()
{
    if (PlayerCharacter)
    {
        UE_LOG(LogTemp, Log, TEXT("%s: Calling DropItem with %s"), *FString(__FUNCTION__),
            *OriginatingItemSlot->InternalItemReference->TextData.Name.ToString());
        PlayerCharacter->DropItem(OriginatingItemSlot->InternalItemReference);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s: DropItem could not be completed, player character reference was nullptr!"), 
            *FString(__FUNCTION__));
    }

    CloseSubmenu();
}

void UInventorySubmenu::SplitButtonClicked()
{
    if (bItemCanBeSplit && AmountWidget)
    {
        bSplitInProgress = true;
        CloseSubmenu();

        // Configure Amount Widget
        AmountWidget->SetHeaderText(FText::FromString("Amount to split:"));
        AmountWidget->SetItemReference(OriginatingItemSlot->InternalItemReference);

        // Position widget at mouse cursor
        float MouseX, MouseY;
        if (!GetOwningPlayer()->GetMousePosition(MouseX, MouseY))
        {
            UE_LOG(LogTemp, Error, TEXT("%s: GetOwningPlayer()->GetMousePosition() returned false!"),
                *FString(__FUNCTION__));
        }
        
        const FVector2D WidgetPosition{MouseX, MouseY};
        AmountWidget->SetPositionInViewport(WidgetPosition);
        AmountWidget->SetAlignmentInViewport(FVector2D{0.5, 0.5});
        AmountWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

//==========================================================================
// SPLIT OPERATION
//==========================================================================
void UInventorySubmenu::SplitConfirmed(const int32 AmountToSplit)
{
    if (AmountToSplit >= OriginatingItemSlot->InternalItemReference->Quantity || AmountToSplit == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s: No split performed. Split amount was equal to item quantity or 0."),
            *FString(__FUNCTION__));
    }
    else
    {
        if (PlayerCharacter)
        {
            PlayerCharacter->GetInventory()->SplitExistingStack(OriginatingItemSlot->InternalItemReference, AmountToSplit);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("%s: Split could not be completed, player character reference was nullptr!"),
                *FString(__FUNCTION__));
        }
    }
    
    bSplitInProgress = false;
}

//==========================================================================
// SUBMENU MANAGEMENT
//==========================================================================
void UInventorySubmenu::CloseSubmenu()
{
    // Do not null OriginatingItemSlot when closing the submenu due to a split
    if (bSplitInProgress)
    {
        bSubMenuActive = false;
        SetVisibility(ESlateVisibility::Collapsed);
    }
    else
    {
        OriginatingItemSlot = nullptr;
        bSplitInProgress = false;
        bSubMenuActive = false;
        SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UInventorySubmenu::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);
    CloseSubmenu();
}