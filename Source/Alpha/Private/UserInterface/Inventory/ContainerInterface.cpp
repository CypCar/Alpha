#include "UserInterface/Inventory/ContainerInterface.h"

//==========================================================================
// INCLUDES
//==========================================================================
// Game
#include "World/LootContainer.h"
#include "UserInterface/Inventory/InventoryPanel.h"
#include "Alpha/AlphaCharacter.h"
#include "Components/InventoryComponent.h"
#include "Items/ItemBase.h"

// Engine
#include "Components/Button.h"

//==========================================================================
// WIDGET INITIALIZATION & CLEANUP
//==========================================================================
void UContainerInterface::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    // Bind Button Events
    if (CloseButton)
    {
        CloseButton->OnClicked.AddDynamic(this, &UContainerInterface::HideContainerInterface);
    }

    if (LootAllButton)
    {
        LootAllButton->OnClicked.AddDynamic(this, &UContainerInterface::LootAllItems);
    }

    // Find Player Character Reference
    PlayerCharacter = Cast<AAlphaCharacter>(GetOwningPlayerPawn());
}

void UContainerInterface::NativeDestruct()
{
    // Clean up when widget is being destroyed
    ClearTargetContainer();
    Super::NativeDestruct();
}

//==========================================================================
// CONTAINER LINKING SYSTEM
//==========================================================================
void UContainerInterface::LinkContainerInterface(AContainer* InContainer)
{
    TargetContainer = InContainer;

    if (!ContainerInventoryPanel || !TargetContainer)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s: Missing panel or container."), ANSI_TO_TCHAR(__FUNCTION__));
        return;
    }

    // Link inventory panel to container's inventory
    ContainerInventoryPanel->LinkToInventory(TargetContainer->GetContainerInventory());
}

void UContainerInterface::ClearTargetContainer()
{
    if (ContainerInventoryPanel && ContainerInventoryPanel->bIsLinkedToInventory)
    {
        ContainerInventoryPanel->UnlinkFromInventory();
    }

    UE_LOG(LogTemp, Log, TEXT("%s: Nulling TargetContainer reference in %s."), 
        ANSI_TO_TCHAR(__FUNCTION__), *GetName());
    TargetContainer = nullptr;
}

//==========================================================================
// UI MANAGEMENT
//==========================================================================
void UContainerInterface::HideContainerInterface()
{
    if (CloseContainerInterface.ExecuteIfBound(true))
    {
        UE_LOG(LogTemp, Log, TEXT("%s: Closing container interface via delegate."), 
            ANSI_TO_TCHAR(__FUNCTION__));
    }
}

//==========================================================================
// LOOTING SYSTEM
//==========================================================================
void UContainerInterface::LootAllItems()
{
    if (!TargetContainer || !PlayerCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s: Missing target container or player character!"), 
            ANSI_TO_TCHAR(__FUNCTION__));
        return;
    }

    UInventoryComponent* ContainerInventory = TargetContainer->GetContainerInventory();
    UInventoryComponent* PlayerInventory = PlayerCharacter->GetInventory();

    if (!ContainerInventory || !PlayerInventory)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s: Missing container or player inventory!"), 
            ANSI_TO_TCHAR(__FUNCTION__));
        return;
    }

    // Get a copy of items list (original may change during iteration)
    TArray<UItemBase*> ItemsToLoot = ContainerInventory->GetInventoryContents();

    int32 LootedCount = 0;
    for (UItemBase* Item : ItemsToLoot)
    {
        if (Item)
        {
            LootSingleItem(Item);
            LootedCount++;
        }
    }

    UE_LOG(LogTemp, Log, TEXT("%s: Looted %d items from container"), 
        ANSI_TO_TCHAR(__FUNCTION__), LootedCount);

    // NEW: Close interface if container is empty after looting
    if (ContainerInventory->GetInventoryContents().Num() == 0)
    {
        UE_LOG(LogTemp, Log, TEXT("%s: Container is now empty, closing container interface."), 
            ANSI_TO_TCHAR(__FUNCTION__));
        HideContainerInterface();
    }
}

void UContainerInterface::LootSingleItem(UItemBase* Item)
{
    if (!Item || !PlayerCharacter || !TargetContainer)
    {
        return;
    }

    UInventoryComponent* PlayerInventory = PlayerCharacter->GetInventory();
    UInventoryComponent* ContainerInventory = TargetContainer->GetContainerInventory();

    if (!PlayerInventory || !ContainerInventory)
    {
        return;
    }

    // Transfer item to player's inventory
    const FItemAddResult AddResult = PlayerInventory->HandleAddItem(Item);

    if (AddResult.OperationResult == EItemAddResult::IAR_AllItemsAdded || 
        AddResult.OperationResult == EItemAddResult::IAR_PartialAmountItemAdded)
    {
        // Remove item from container (or update quantity)
        ContainerInventory->HandleRemoveItem(Item);

        // Create and send loot notification
        FInteractableData LootData = CreateLootDataFromItem(Item, AddResult.AmountAdded);
        
        // Trigger notification on container
        TargetContainer->NotifyItemLooted(LootData);

        UE_LOG(LogTemp, Verbose, TEXT("%s: Looted %s x%d"), 
            ANSI_TO_TCHAR(__FUNCTION__), *Item->TextData.Name.ToString(), AddResult.AmountAdded);
    }
}

FInteractableData UContainerInterface::CreateLootDataFromItem(UItemBase* Item, int32 Quantity) const
{
    FInteractableData LootData;
    
    if (Item)
    {
        LootData.Name = Item->TextData.Name;
        LootData.Quantity = Quantity;
        LootData.Action = FText::FromString("Looted");
        LootData.InteractableType = EInteractableType::Container;
    }
    
    return LootData;
}