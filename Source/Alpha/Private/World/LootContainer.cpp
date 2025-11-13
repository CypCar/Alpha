#include "World/LootContainer.h"

//==========================================================================
// INCLUDES
//==========================================================================
// Engine
#include "Engine/DataTable.h"
#include "Components/StaticMeshComponent.h"

// Game
#include "Components/InventoryComponent.h"
#include "Items/ItemBase.h"
#include "Alpha/AlphaCharacter.h"
#include "Data/ItemDataStructs.h"

//==========================================================================
// CONSTRUCTOR
//==========================================================================
AContainer::AContainer()
{
    PrimaryActorTick.bCanEverTick = false;

    // Mesh Component Setup
    ContainerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ContainerMesh"));
    SetRootComponent(ContainerMesh);

    // Collision Setup for Interaction System
    ContainerMesh->SetCollisionObjectType(ECC_GameTraceChannel1);
    ContainerMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ContainerMesh->SetGenerateOverlapEvents(true);

    // Inventory Component Setup
    ContainerInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("ContainerInventory"));

    // Default Interaction Text
    ContainerName = FText::FromString(TEXT("Container"));
    OpenActionText = FText::FromString(TEXT("Open"));
    InteractionDuration = 0.0f;

    // Initialize Interactable Data
    InteractableData.InteractableType = EInteractableType::Container;
    InteractableData.Name = ContainerName;
    InteractableData.Action = OpenActionText;
    InteractableData.Quantity = 0; // Hidden in widget for Container
    InteractableData.InteractionDuration = InteractionDuration;
}

//==========================================================================
// GAME FLOW
//==========================================================================
void AContainer::BeginPlay()
{
    Super::BeginPlay();

    BuildInteractableData();
    PopulateContainerFromDefaults();
}

void AContainer::BuildInteractableData()
{
    InteractableData.InteractableType = EInteractableType::Container;
    InteractableData.Name = ContainerName;
    InteractableData.Action = OpenActionText;
    InteractableData.InteractionDuration = InteractionDuration;
}

//==========================================================================
// INTERACTION INTERFACE
//==========================================================================
void AContainer::BeginFocus()
{
    if (ContainerMesh)
    {
        ContainerMesh->SetRenderCustomDepth(true);
    }
}

void AContainer::EndFocus()
{
    if (ContainerMesh)
    {
        ContainerMesh->SetRenderCustomDepth(false);
    }
}

void AContainer::Interact(AAlphaCharacter* PlayerCharacter)
{
    // Actual UI opening is handled in AAlphaCharacter::Interact()
    // This can be used for SFX/animations if desired
}

//==========================================================================
// INVENTORY MANAGEMENT
//==========================================================================
FItemAddResult AContainer::AddItemToContainer(UItemBase* ItemToAdd)
{
    if (!ContainerInventory || !ItemToAdd)
    {
        return FItemAddResult::AddedNone(FText::FromString(TEXT("Invalid container inventory or item.")));
    }

    return ContainerInventory->HandleAddItem(ItemToAdd);
}

FItemAddResult AContainer::AddItemFromRowHandle(const FDataTableRowHandle& ItemRowHandle, int32 Quantity)
{
    if (ItemRowHandle.IsNull())
    {
        return FItemAddResult::AddedNone(FText::FromString(TEXT("ItemRowHandle is null.")));
    }

    const FString ContextString = TEXT("AContainer::AddItemFromRowHandle");
    const FItemData* ItemData = ItemRowHandle.GetRow<FItemData>(ContextString);
    
    if (!ItemData)
    {
        return FItemAddResult::AddedNone(FText::FromString(TEXT("Failed to get row from ItemRowHandle.")));
    }

    // Create item instance - same as in APickup
    UItemBase* NewItem = NewObject<UItemBase>(this, UItemBase::StaticClass());
    if (!NewItem)
    {
        return FItemAddResult::AddedNone(FText::FromString(TEXT("Failed to create UItemBase instance.")));
    }

    // Initialize Item Properties
    NewItem->ID = ItemData->ID;
    NewItem->ItemType = ItemData->ItemType;
    NewItem->ItemQuality = ItemData->ItemQuality;
    NewItem->NumericData = ItemData->NumericData;
    NewItem->TextData = ItemData->TextData;
    NewItem->AssetData = ItemData->AssetData;
    NewItem->ItemStatistics = ItemData->ItemStatistics;

    NewItem->NumericData.bIsStackable = ItemData->NumericData.MaxStackSize > 1;

    // Set Quantity
    Quantity <= 0 ? NewItem->SetQuantity(1) : NewItem->SetQuantity(Quantity);

    return AddItemToContainer(NewItem);
}

void AContainer::PopulateContainerFromDefaults()
{
    if (!ContainerInventory)
    {
        UE_LOG(LogTemp, Warning, TEXT("PopulateContainerFromDefaults: ContainerInventory is null!"));
        return;
    }

    // Find default DataTable from first valid entry
    const UDataTable* DefaultTable = nullptr;
    for (int32 i = 0; i < DefaultItems.Num(); ++i)
    {
        const FContainerItemEntry& Entry = DefaultItems[i];

        if (Entry.ItemRowHandle.DataTable && !Entry.ItemRowHandle.RowName.IsNone())
        {
            DefaultTable = Entry.ItemRowHandle.DataTable;
            
            UE_LOG(LogTemp, Log,
                TEXT("PopulateContainerFromDefaults: Using DefaultTable from entry %d (%s)"),
                i,
                *Entry.ItemRowHandle.DataTable->GetName());
            break;
        }
    }

    if (!DefaultTable)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("PopulateContainerFromDefaults: No valid DataTable found in DefaultItems! Nothing will be added."));
    }

    // Process each default item entry
    for (int32 i = 0; i < DefaultItems.Num(); ++i)
    {
        const FContainerItemEntry& Entry = DefaultItems[i];

        UE_LOG(LogTemp, Log,
            TEXT("PopulateContainerFromDefaults: Entry %d -> Qty=%d, RowName=%s, DataTable=%s"),
            i,
            Entry.Quantity,
            *Entry.ItemRowHandle.RowName.ToString(),
            Entry.ItemRowHandle.DataTable ? *Entry.ItemRowHandle.DataTable->GetName() : TEXT("nullptr"));

        // Skip invalid quantities
        if (Entry.Quantity <= 0)
        {
            UE_LOG(LogTemp, Warning,
                TEXT("PopulateContainerFromDefaults: Entry %d has non-positive Quantity (%d). Skipping."),
                i, Entry.Quantity);
            continue;
        }

        // Copy RowHandle for local modification
        FDataTableRowHandle RowHandle = Entry.ItemRowHandle;

        // Use default table if this entry doesn't have one
        if (!RowHandle.DataTable && DefaultTable)
        {
            RowHandle.DataTable = const_cast<UDataTable*>(DefaultTable);
            
            UE_LOG(LogTemp, Log,
                TEXT("PopulateContainerFromDefaults: Entry %d had no DataTable, using DefaultTable '%s'."),
                i,
                *DefaultTable->GetName());
        }

        // Skip invalid entries
        if (!RowHandle.DataTable || RowHandle.RowName.IsNone())
        {
            UE_LOG(LogTemp, Warning,
                TEXT("PopulateContainerFromDefaults: Entry %d has invalid RowHandle (DataTable=%s, RowName=%s). Skipping."),
                i,
                RowHandle.DataTable ? *RowHandle.DataTable->GetName() : TEXT("nullptr"),
                *RowHandle.RowName.ToString());
            continue;
        }

        // Add item to container
        FItemAddResult Result = AddItemFromRowHandle(RowHandle, Entry.Quantity);

        UE_LOG(LogTemp, Log,
            TEXT("PopulateContainerFromDefaults: AddItemFromRowHandle entry %d (RowName=%s, Qty=%d) -> Result=%d, AmountAdded=%d, Msg=%s"),
            i,
            *RowHandle.RowName.ToString(),
            Entry.Quantity,
            static_cast<int32>(Result.OperationResult),
            Result.AmountAdded,
            *Result.ResultMessage.ToString());

        if (Result.OperationResult == EItemAddResult::IAR_NoItemAdded)
        {
            UE_LOG(LogTemp, Warning,
                TEXT("AContainer::PopulateContainerFromDefaults: Failed to add item from row '%s': %s"),
                *RowHandle.RowName.ToString(),
                *Result.ResultMessage.ToString());
        }
    }

    // Log final container contents
    const TArray<UItemBase*> ItemsInInv = ContainerInventory->GetInventoryContents();
    UE_LOG(LogTemp, Log,
        TEXT("PopulateContainerFromDefaults: ContainerInventory has %d items after population."),
        ItemsInInv.Num());

    for (int32 idx = 0; idx < ItemsInInv.Num(); ++idx)
    {
        if (const UItemBase* Item = ItemsInInv[idx])
        {
            UE_LOG(LogTemp, Log,
                TEXT("  Slot %d: %s x%d (ID=%s)"),
                idx,
                *Item->TextData.Name.ToString(),
                Item->Quantity,
                *Item->ID.ToString());
        }
    }
}

//==========================================================================
// LOOT SYSTEM
//==========================================================================
void AContainer::NotifyItemLooted(const FInteractableData& LootData)
{
    UE_LOG(LogTemp, Log, TEXT("Item looted from container: %s x%d"),
        *LootData.Name.ToString(),
        LootData.Quantity);

    // Call Blueprint event with simple types
    OnItemLooted(LootData.Name, LootData.Quantity);

    // Example: destroy container when empty
    // if (ContainerInventory && ContainerInventory->GetInventoryContents().Num() == 0)
    // {
    //     Destroy();
    // }
}