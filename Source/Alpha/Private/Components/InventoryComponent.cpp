#include "Components/InventoryComponent.h"
#include "Items/ItemBase.h"

#define DEBUG_TO_SCREEN(Message) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString(__FUNCTION__) + "(" + FString::FromInt(__LINE__) + ") " + Message);

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent(): InventoryTotalWeight(0.0), ItemSlotCount(10), MaxWeightCapacity(20.0)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

UItemBase* UInventoryComponent::FindMatchingItem(const TObjectPtr<UItemBase>& ItemIn) const
{
	if (ItemIn)
	{
		if (InventoryContents.Contains(ItemIn))
		{
			return ItemIn;
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextItemByID(const TObjectPtr<UItemBase>& ItemIn) const
{
	if (ItemIn)
	{
		if (const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByKey(ItemIn))
		{
			return *Result;
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextPartialStack(const TObjectPtr<UItemBase>& ItemIn) const
{
	if (const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByPredicate(
		[&ItemIn](const UItemBase* InventoryItem)
		{
			return InventoryItem->ID == ItemIn->ID && !InventoryItem->IsFullItemStack();
		})
	)
	{
		return *Result;
	}

	return nullptr;
}

int32 UInventoryComponent::CalculateWeightAddAmount(const TObjectPtr<UItemBase>& ItemIn, const int32 RequestedAddAmount) const
{
	const int32 WeightMaxAddAmount = FMath::FloorToInt((MaxWeightCapacity - InventoryTotalWeight) / ItemIn->GetItemSingleWeight());
	if (WeightMaxAddAmount >= RequestedAddAmount)
	{
		return RequestedAddAmount;
	}
	return WeightMaxAddAmount;
}

int32 UInventoryComponent::CalculateNumberForFullStack(const TObjectPtr<UItemBase>& StackableItem, const int32 RequestedAddAmount) const
{
	const int32 AddAmountToMakeFullStack = StackableItem->NumericData.MaxStackSize - StackableItem->Quantity;
	return FMath::Min(RequestedAddAmount, AddAmountToMakeFullStack);
}

void UInventoryComponent::MergeItems(const TObjectPtr<UItemBase>& TargetItem, const TObjectPtr<UItemBase>& SourceItem)
{
	const int32 AmountToShift = CalculateNumberForFullStack(TargetItem, SourceItem->Quantity);

	if (AmountToShift > 0)
	{
		TargetItem->SetQuantity(TargetItem->Quantity + AmountToShift);
		// weight isn't changing, so don't let HandleRemoveItem adjust it
		HandleRemoveItem(SourceItem, AmountToShift, false);
	}
}

void UInventoryComponent::HandleRemoveItem(UItemBase* ItemToRemove, int32 AmountToRemove, const bool bAdjustWeight)
{
	if (!ItemToRemove) return;

	// Czy usuwamy cały wpis (Amount<=0 traktuj jako "usuń cały")
	const bool bRemoveWholeEntry = (AmountToRemove <= 0) || (AmountToRemove >= ItemToRemove->Quantity);

	if (bRemoveWholeEntry)
	{
		if (bAdjustWeight)
		{
			InventoryTotalWeight -= ItemToRemove->GetItemSingleWeight() * ItemToRemove->Quantity;
			InventoryTotalWeight = FMath::Max(0.f, InventoryTotalWeight); // bez ujemnych
		}

		InventoryContents.RemoveSingle(ItemToRemove);
		InventoryWasUpdated.Broadcast();
		return;
	}

	// Częściowe zdejmowanie sztuk ze stacka
	ItemToRemove->SetQuantity(ItemToRemove->Quantity - AmountToRemove);

	if (bAdjustWeight)
	{
		InventoryTotalWeight -= ItemToRemove->GetItemSingleWeight() * AmountToRemove;
		InventoryTotalWeight = FMath::Max(0.f, InventoryTotalWeight);
	}

	InventoryWasUpdated.Broadcast();
}

void UInventoryComponent::SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit)
{
	// since you're not technically *removing* an item by splitting, the split
	// process manipulates the inventory array directly

	if (InventoryContents.Num() + 1 <= ItemSlotCount)
	{
		UItemBase* SplitPortion = UItemBase::CreateItemCopy(ItemIn, this);
		SplitPortion->SetQuantity(AmountToSplit);
		InventoryContents.Add(SplitPortion);

		ItemIn->Quantity -= AmountToSplit;

		InventoryWasUpdated.Broadcast();
	}
}

FItemAddResult UInventoryComponent::HandleNonStackableItems(const TObjectPtr<UItemBase>& InputItem)
{
	// check if in the input item has valid weight
	if (FMath::IsNearlyZero(InputItem->GetItemSingleWeight()) || InputItem->GetItemSingleWeight() < 0)
	{
		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("Could not add {0} to the inventory. Item has invalid weight value."),
			InputItem->TextData.Name));
	}

	// check if the item weight will overflow weight capacity
	if (InventoryTotalWeight + InputItem->GetItemSingleWeight() > MaxWeightCapacity)
	{
		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("Could not add {0} to the inventory. Item would overflow weight limit."),
			InputItem->TextData.Name));
	}

	// check if adding one more item would overflow slot capacity
	if (InventoryContents.Num() + 1 > ItemSlotCount)
	{
		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("Could not add {0} to the inventory. All inventory slots are full."),
			InputItem->TextData.Name));
	}

	AddNewItem(InputItem, 1);

	return FItemAddResult::AddedAll(
		1, FText::Format(FText::FromString("Successfully added a single {0} to the inventory."), InputItem->TextData.Name));
}

int32 UInventoryComponent::HandleStackableItems(const TObjectPtr<UItemBase>& ItemIn, const int32 RequestedAddAmount)
{
	if (RequestedAddAmount <= 0 || FMath::IsNearlyZero(ItemIn->GetItemStackWeight()))
	{
		// invalid item data
		return 0;
	}

	int32 AmountToDistribute = RequestedAddAmount;

	// check if the input item already exists in the inventory and is not a full stack
	UItemBase* ExistingItemStack = FindNextPartialStack(ItemIn);

	// distribute item stack over existing stacks
	while (ExistingItemStack)
	{
		// calculate how many of the existing item would be needed to make the next full stack
		const int32 AmountToMakeFullStack = CalculateNumberForFullStack(ExistingItemStack, AmountToDistribute);
		// calculate how many of the AmountToMakeFullStack can actually be carried based on weight capacity
		const int32 WeightLimitAddAmount = CalculateWeightAddAmount(ExistingItemStack, AmountToMakeFullStack);

		// as long as the remaining amount of the item does not overflow weight capacity
		if (WeightLimitAddAmount > 0)
		{
			// adjust the existing items stack quantity and inventory total weight
			ExistingItemStack->SetQuantity(ExistingItemStack->Quantity + WeightLimitAddAmount);

			InventoryTotalWeight += (ExistingItemStack->GetItemSingleWeight() * WeightLimitAddAmount);

			// adjust the count to be distributed
			AmountToDistribute -= WeightLimitAddAmount;

			// if max weight capacity would be exceeded by another item, just return early
			if (InventoryTotalWeight + ExistingItemStack->GetItemSingleWeight() > MaxWeightCapacity)
			{
				InventoryWasUpdated.Broadcast();
				return RequestedAddAmount - AmountToDistribute;
			}
		}
		else if (WeightLimitAddAmount <= 0)
		{
			if (AmountToDistribute != RequestedAddAmount)
			{
				// this block will be reached if distributing an item across multiple stacks
				// and the weight limit is hit during that process
				InventoryWasUpdated.Broadcast();
				return RequestedAddAmount - AmountToDistribute;
			}

			// reached if there is a partial stack but none of it can be added at all
			return 0;
		}

		if (AmountToDistribute <= 0)
		{
			// all of the input item was distributed across existing stacks
			InventoryWasUpdated.Broadcast();
			return RequestedAddAmount;
		}

		// check if there is still another valid partial stack of the input item
		ExistingItemStack = FindNextPartialStack(ItemIn);
	}

	// no more partial stacks found, check if a new stack can be added
	if (InventoryContents.Num() + 1 <= ItemSlotCount)
	{
		// attempt to add as many from the remaining item quantity that can fit inventory weight capacity
		const int32 WeightLimitAddAmount = CalculateWeightAddAmount(ItemIn, AmountToDistribute);

		if (WeightLimitAddAmount > 0)
		{
			// if there is still more item to distribute, but weight limit has been reached
			if (WeightLimitAddAmount < AmountToDistribute)
			{
				// adjust the input item and add a new stack with as many as can be held
				AmountToDistribute -= WeightLimitAddAmount;
				ItemIn->SetQuantity(AmountToDistribute);

				// add the new partial stack with WeightLimitAddAmount as quantity 
				AddNewItem(ItemIn, WeightLimitAddAmount);
				return RequestedAddAmount - AmountToDistribute;
			}

			// otherwise, the full remainder of the stack can be added
			AddNewItem(ItemIn, AmountToDistribute);
			return RequestedAddAmount;
		}

		// reached if there is free item slots, but no remaining weight capacity
		return RequestedAddAmount - AmountToDistribute;
	}

	// can only be reached if there is no existing stack and no extra capacity slots
	return 0;
}

FItemAddResult UInventoryComponent::HandleAddItem(const TObjectPtr<UItemBase>& InputItem)
{
	const int32 InitialRequestedAddAmount = InputItem->Quantity;

	// handle non-stackable items
	if (!InputItem->NumericData.bIsStackable)
	{
		return HandleNonStackableItems(InputItem);
	}

	// handle stackable
	const int32 StackableAmountAdded = HandleStackableItems(InputItem, InitialRequestedAddAmount);

	if (StackableAmountAdded == InitialRequestedAddAmount)
	{
		return FItemAddResult::AddedAll(InitialRequestedAddAmount, FText::Format(
			                                FText::FromString("Successfully added {0} {1} to the inventory."),
			                                InitialRequestedAddAmount,
			                                InputItem->TextData.Name));
	}

	if (StackableAmountAdded < InitialRequestedAddAmount && StackableAmountAdded > 0)
	{
		return FItemAddResult::AddedPartial(StackableAmountAdded, FText::Format(
			                                    FText::FromString("Partial amount of {0} added to the inventory. Number added = {1}"),
			                                    InputItem->TextData.Name,
			                                    StackableAmountAdded));
	}

	if (StackableAmountAdded <= 0)
	{
		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("Couldn't add {0} to the inventory. No remaining inventory slots, or invalid item."),
			InputItem->TextData.Name));
	}

	return FItemAddResult::AddedNone(FText::FromString("TryAddItem fallthrough error."));
}

void UInventoryComponent::AddNewItem(const TObjectPtr<UItemBase>& Item, const int32 AmountToAdd)
{
	UItemBase* NewItem = UItemBase::CreateItemCopy(Item, this);
	NewItem->SetQuantity(AmountToAdd);
	InventoryContents.Add(NewItem);
	InventoryTotalWeight += NewItem->GetItemStackWeight();
	InventoryWasUpdated.Broadcast();
}

EItemUseResult UInventoryComponent::UseItemForActor(UItemBase* ItemToUse, AActor* UserActor)
{
    UE_LOG(LogTemp, Warning, TEXT("UseItemForActor: Item=%s (Type=%d, Heal=%.2f, Qty=%d), Actor=%s"),
        ItemToUse ? *ItemToUse->TextData.Name.ToString() : TEXT("<null>"),
        ItemToUse ? (int32)ItemToUse->ItemType : -1,
        ItemToUse ? ItemToUse->ItemStatistics.RestorationAmount : -1.f,
        ItemToUse ? ItemToUse->Quantity : -1,
        UserActor ? *UserActor->GetName() : TEXT("<null>"));

    if (!ItemToUse || !UserActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("UseItemForActor: nullptr (Item or Actor)"));
        return EItemUseResult::IUR_Failed;
    }

    if (ItemToUse->ItemType != EItemType::Consumable)
    {
        UE_LOG(LogTemp, Warning, TEXT("UseItemForActor: WrongType (%d) for '%s'"),
            (int32)ItemToUse->ItemType, *ItemToUse->TextData.Name.ToString());
        return EItemUseResult::IUR_WrongType;
    }

    const float HealAmount = ItemToUse->ItemStatistics.RestorationAmount;
    if (HealAmount <= 0.f)
    {
        UE_LOG(LogTemp, Warning, TEXT("UseItemForActor: HealAmount <= 0 (%.2f) for '%s'"),
            HealAmount, *ItemToUse->TextData.Name.ToString());
        return EItemUseResult::IUR_Failed;
    }

    UStatsComponent* Stats = UserActor->FindComponentByClass<UStatsComponent>();
    if (!Stats)
    {
        UE_LOG(LogTemp, Warning, TEXT("UseItemForActor: No UStatsComponent on %s"), *UserActor->GetName());
        return EItemUseResult::IUR_NoStats;
    }

    const float Cur = Stats->GetCurrentHealth();
    const float Max = Stats->GetMaxHealth();
    if (Cur >= Max)
    {
        UE_LOG(LogTemp, Warning, TEXT("UseItemForActor: Full HP (%.2f/%.2f) for '%s'"),
            Cur, Max, *ItemToUse->TextData.Name.ToString());
        return EItemUseResult::IUR_Failed; // zmień na NoEffect jeśli chcesz odróżniać
    }

    UE_LOG(LogTemp, Warning, TEXT("UseItemForActor: BEFORE Heal -> %.2f/%.2f, Heal=%.2f"), Cur, Max, HealAmount);
    Stats->Heal(HealAmount);
    const float After = Stats->GetCurrentHealth();
    const float Applied = After - Cur;

    if (Applied <= 0.f)
    {
        UE_LOG(LogTemp, Warning, TEXT("UseItemForActor: Applied <= 0 (Before=%.2f, After=%.2f)"), Cur, After);
        return EItemUseResult::IUR_Failed;
    }

    HandleRemoveItem(ItemToUse, 1, true);
    UE_LOG(LogTemp, Log, TEXT("UseItemForActor: SUCCESS Heal=%.2f → Now %.2f/%.2f"), Applied, After, Max);
    return EItemUseResult::IUR_Success;
}