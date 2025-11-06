#include "World/LootContainer.h"

// game
#include "Components/StaticMeshComponent.h"
#include "Components/InventoryComponent.h"
#include "Items/ItemBase.h"
#include "Alpha/AlphaCharacter.h"
#include "Data/ItemDataStructs.h"  // FItemData

// engine
#include "Engine/DataTable.h"

AContainer::AContainer()
{
	PrimaryActorTick.bCanEverTick = false;

	// --- Mesh jako root ---
	ContainerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ContainerMesh"));
	SetRootComponent(ContainerMesh);

	// BARDZO WAŻNE: żeby system interakcji (trace) widział kontener tak jak pickup
	// pickup ma: PickupMesh->SetCollisionObjectType(ECC_GameTraceChannel1);
	ContainerMesh->SetCollisionObjectType(ECC_GameTraceChannel1);
	ContainerMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ContainerMesh->SetGenerateOverlapEvents(true);

	// --- Inventory ---
	ContainerInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("ContainerInventory"));

	// Domyślne teksty (do zmiany w BP / w detailsach)
	ContainerName       = FText::FromString(TEXT("Container"));
	OpenActionText      = FText::FromString(TEXT("Open"));
	InteractionDuration = 0.0f;

	// Ustaw podstawowe dane interakcji
	InteractableData.InteractableType     = EInteractableType::Container;
	InteractableData.Name                 = ContainerName;
	InteractableData.Action               = OpenActionText;
	InteractableData.Quantity             = 0;          // ukrywane w widgetcie dla Container
	InteractableData.InteractionDuration  = InteractionDuration;
}

void AContainer::BeginPlay()
{
	Super::BeginPlay();

	BuildInteractableData();

	// Na starcie zasila się domyślnym lootem (jak coś skonfigurowałeś w Detailsach)
	PopulateContainerFromDefaults();
}

void AContainer::BuildInteractableData()
{
	InteractableData.InteractableType    = EInteractableType::Container;
	InteractableData.Name                = ContainerName;
	InteractableData.Action              = OpenActionText;
	InteractableData.InteractionDuration = InteractionDuration;
}

// ==========================
// IInteractionInterface
// ==========================

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
	// Faktyczne otwarcie UI robisz już w AAlphaCharacter::Interact()
	// (case EInteractableType::Container → HUD->SetTargetContainer(...))
	// Tutaj możesz dorzucić SFX/animację itp. jeśli chcesz.
}

// ==========================
// API kontenera
// ==========================

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

	// Tworzymy instancję itemu – dokładnie jak w APickup
	UItemBase* NewItem = NewObject<UItemBase>(this, UItemBase::StaticClass());
	if (!NewItem)
	{
		return FItemAddResult::AddedNone(FText::FromString(TEXT("Failed to create UItemBase instance.")));
	}

	NewItem->ID          = ItemData->ID;
	NewItem->ItemType    = ItemData->ItemType;
	NewItem->ItemQuality = ItemData->ItemQuality;
	NewItem->NumericData = ItemData->NumericData;
	NewItem->TextData    = ItemData->TextData;
	NewItem->AssetData   = ItemData->AssetData;

	NewItem->NumericData.bIsStackable = ItemData->NumericData.MaxStackSize > 1;

	if (Quantity <= 0)
	{
		NewItem->SetQuantity(1);
	}
	else
	{
		NewItem->SetQuantity(Quantity);
	}

	return AddItemToContainer(NewItem);
}

void AContainer::PopulateContainerFromDefaults()
{
	if (!ContainerInventory)
	{
		return;
	}

	// Znajdź domyślną DataTable z pierwszego poprawnego wpisu
	const UDataTable* DefaultTable = nullptr;
	for (const FContainerItemEntry& Entry : DefaultItems)
	{
		if (Entry.ItemRowHandle.DataTable && !Entry.ItemRowHandle.RowName.IsNone())
		{
			DefaultTable = Entry.ItemRowHandle.DataTable;
			break;
		}
	}

	for (const FContainerItemEntry& Entry : DefaultItems)
	{
		if (Entry.Quantity <= 0)
		{
			continue;
		}

		// Skopiuj RowHandle, żeby można było go modyfikować lokalnie
		FDataTableRowHandle RowHandle = Entry.ItemRowHandle;

		// Jeśli DataTable nie jest ustawione w tym wpisie – spróbuj użyć domyślnej
		if (!RowHandle.DataTable)
		{
			RowHandle.DataTable = DefaultTable;
		}

		// Jeśli dalej nie ma DataTable albo brak RowName – odpuść
		if (!RowHandle.DataTable || RowHandle.RowName.IsNone())
		{
			UE_LOG(LogTemp, Warning, TEXT("PopulateContainerFromDefaults: Entry has invalid RowHandle (no DataTable or RowName). Skipping."));
			continue;
		}

		FItemAddResult Result = AddItemFromRowHandle(RowHandle, Entry.Quantity);

		if (Result.OperationResult == EItemAddResult::IAR_NoItemAdded)
		{
			UE_LOG(LogTemp, Warning, TEXT("AContainer::PopulateContainerFromDefaults: Failed to add item from row '%s': %s"),
				*RowHandle.RowName.ToString(),
				*Result.ResultMessage.ToString());
		}
	}
}


void AContainer::NotifyItemLooted(const FInteractableData& LootData)
{
	UE_LOG(LogTemp, Log, TEXT("Item looted from container: %s x%d"),
		*LootData.Name.ToString(),
		LootData.Quantity);

	// Wywołujemy event Blueprintowy z prostymi typami
	OnItemLooted(LootData.Name, LootData.Quantity);

	// Przykład: zniszcz kontener jak jest pusty
	// if (ContainerInventory && ContainerInventory->GetInventoryContents().Num() == 0)
	// {
	//     Destroy();
	// }
}
