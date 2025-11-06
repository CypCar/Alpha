#include "UserInterface/Inventory/ContainerInterface.h"

// game
#include "World/LootContainer.h"
#include "UserInterface/Inventory/InventoryPanel.h"
#include "Alpha/AlphaCharacter.h"
#include "Components/InventoryComponent.h"
#include "Items/ItemBase.h"

// engine
#include "Components/Button.h"

void UContainerInterface::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (CloseButton)
    {
        CloseButton->OnClicked.AddDynamic(this, &UContainerInterface::HideContainerInterface);
    }

    if (LootAllButton)
    {
        LootAllButton->OnClicked.AddDynamic(this, &UContainerInterface::LootAllItems);
    }

    // Znajdź gracza
    PlayerCharacter = Cast<AAlphaCharacter>(GetOwningPlayerPawn());
}

void UContainerInterface::NativeDestruct()
{
    // Oczyść przy odinstalowywaniu
    ClearTargetContainer();
    Super::NativeDestruct();
}

void UContainerInterface::LinkContainerInterface(AContainer* InContainer)
{
    TargetContainer = InContainer;

    if (!ContainerInventoryPanel || !TargetContainer)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s: Missing panel or container."), ANSI_TO_TCHAR(__FUNCTION__));
        return;
    }

    ContainerInventoryPanel->LinkToInventory(TargetContainer->GetContainerInventory());
}

void UContainerInterface::ClearTargetContainer()
{
    if (ContainerInventoryPanel && ContainerInventoryPanel->bIsLinkedToInventory)
    {
        ContainerInventoryPanel->UnlinkFromInventory();
    }

    UE_LOG(LogTemp, Log, TEXT("%s: Nulling TargetContainer reference in %s."), ANSI_TO_TCHAR(__FUNCTION__), *GetName());
    TargetContainer = nullptr;
}

void UContainerInterface::HideContainerInterface()
{
    if (CloseContainerInterface.ExecuteIfBound(true))
    {
        UE_LOG(LogTemp, Log, TEXT("%s: Closing container interface via delegate."), ANSI_TO_TCHAR(__FUNCTION__));
    }
}

void UContainerInterface::LootAllItems()
{
    if (!TargetContainer || !PlayerCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s: Missing target container or player character!"), ANSI_TO_TCHAR(__FUNCTION__));
        return;
    }

    UInventoryComponent* ContainerInventory = TargetContainer->GetContainerInventory();
    UInventoryComponent* PlayerInventory = PlayerCharacter->GetInventory();

    if (!ContainerInventory || !PlayerInventory)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s: Missing container or player inventory!"), ANSI_TO_TCHAR(__FUNCTION__));
        return;
    }

    // Pobierz kopię listy przedmiotów (bo oryginalna może się zmieniać podczas iteracji)
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

    UE_LOG(LogTemp, Log, TEXT("%s: Looted %d items from container"), ANSI_TO_TCHAR(__FUNCTION__), LootedCount);

    
    //  NOWE: jeśli po próbie lootowania kontener jest pusty → zamknij okno
    if (ContainerInventory->GetInventoryContents().Num() == 0)
    {
        UE_LOG(LogTemp, Log, TEXT("%s: Container is now empty, closing container interface."), ANSI_TO_TCHAR(__FUNCTION__));
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

    // Przenieś przedmiot do ekwipunku gracza
    const FItemAddResult AddResult = PlayerInventory->HandleAddItem(Item);

    if (AddResult.OperationResult == EItemAddResult::IAR_AllItemsAdded || 
        AddResult.OperationResult == EItemAddResult::IAR_PartialAmountItemAdded)
    {
        // Usuń przedmiot z kontenera (lub zaktualizuj ilość)
        ContainerInventory->HandleRemoveItem(Item);

        // Stwórz i wyślij powiadomienie
        FInteractableData LootData = CreateLootDataFromItem(Item, AddResult.AmountAdded);
        
        // Wywołaj powiadomienie na kontenerze
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