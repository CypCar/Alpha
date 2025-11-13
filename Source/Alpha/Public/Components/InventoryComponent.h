#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UItemBase;

//==========================================================================
// DELEGATES
//==========================================================================
DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);

//==========================================================================
// ENUMS
//==========================================================================

/**
 * Result of item addition operation
 */
UENUM(BlueprintType)
enum class EItemAddResult : uint8
{
	IAR_NoItemAdded UMETA(DisplayName = "No item added"),
	IAR_PartialAmountItemAdded UMETA(DisplayName = "Partial amount of item added"),
	IAR_AllItemsAdded UMETA(DisplayName = "All of item added")
};

/**
 * Result of item usage operation
 */
UENUM(BlueprintType)
enum class EItemUseResult : uint8
{
	IUR_Failed            UMETA(DisplayName="Failed"),
	IUR_WrongType         UMETA(DisplayName="Wrong type"),
	IUR_NoStats           UMETA(DisplayName="No stats"),
	IUR_NoCharges         UMETA(DisplayName="No charges"),
	IUR_Success           UMETA(DisplayName="Success")
};

//==========================================================================
// STRUCTURES
//==========================================================================

/**
 * Structure containing results of item addition operation
 */
USTRUCT(BlueprintType)
struct FItemAddResult
{
	GENERATED_BODY()

	FItemAddResult() :
		AmountAdded(0),
		OperationResult(EItemAddResult::IAR_NoItemAdded),
		ResultMessage(FText::GetEmpty())
	{};

	// Amount of item that was added to the inventory
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	int32 AmountAdded;

	// Enum representing the end state of an add item operation
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	EItemAddResult OperationResult;

	// Informational message that can be passed with the result
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	FText ResultMessage;

	// Static constructor for failed addition with no items added
	static FItemAddResult AddedNone(const FText& ErrorText)
	{
		FItemAddResult AddedNoneResult;
		AddedNoneResult.AmountAdded = 0;
		AddedNoneResult.OperationResult = EItemAddResult::IAR_NoItemAdded;
		AddedNoneResult.ResultMessage = ErrorText;
		return AddedNoneResult;
	};

	// Static constructor for partial addition
	static FItemAddResult AddedPartial(const int32 PartialAmountAdded, const FText& ErrorText)
	{
		FItemAddResult AddedPartialResult;
		AddedPartialResult.AmountAdded = PartialAmountAdded;
		AddedPartialResult.OperationResult = EItemAddResult::IAR_PartialAmountItemAdded;
		AddedPartialResult.ResultMessage = ErrorText;
		return AddedPartialResult;
	};

	// Static constructor for successful addition of all items
	static FItemAddResult AddedAll(const int32 AmountAdded, const FText& Message)
	{
		FItemAddResult AddedAllResult;
		AddedAllResult.AmountAdded = AmountAdded;
		AddedAllResult.OperationResult = EItemAddResult::IAR_AllItemsAdded;
		AddedAllResult.ResultMessage = Message;
		return AddedAllResult;
	};
};

//==========================================================================
// CLASS: UInventoryComponent
//==========================================================================
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ALPHA_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//==========================================================================
	// CONSTRUCTOR & PUBLIC FUNCTIONS
	//==========================================================================
	UInventoryComponent();

	/**
	 * Attempts to add an item to the inventory
	 * @param InputItem - Item to be added
	 * @return Result of the add operation
	 */
	FItemAddResult HandleAddItem(const TObjectPtr<UItemBase>& InputItem);

	/**
	 * Finds an item in inventory that matches the provided item
	 * @param ItemIn - Item to match against
	 * @return Matching item or nullptr
	 */
	UItemBase* FindMatchingItem(const TObjectPtr<UItemBase>& ItemIn) const;

	/**
	 * Finds the next item with matching ID
	 * @param ItemIn - Item to match ID against
	 * @return Matching item or nullptr
	 */
	UItemBase* FindNextItemByID(const TObjectPtr<UItemBase>& ItemIn) const;

	/**
	 * Finds the next partial stack that can accept more items
	 * @param ItemIn - Item to find stack for
	 * @return Partial stack item or nullptr
	 */
	UItemBase* FindNextPartialStack(const TObjectPtr<UItemBase>& ItemIn) const;

	/**
	 * Merges quantities of two items together that are already in the inventory
	 * @param TargetItem - Item to merge into
	 * @param SourceItem - Item to merge from
	 */
	void MergeItems(const TObjectPtr<UItemBase>& TargetItem, const TObjectPtr<UItemBase>& SourceItem);

	/**
	 * Removes an item from inventory
	 * @param ItemToRemove - Item to remove
	 * @param AmountToRemove - Quantity to remove (0 = remove all)
	 * @param bAdjustWeight - Whether to adjust inventory weight
	 */
	void HandleRemoveItem(UItemBase* ItemToRemove, int32 AmountToRemove = 0, const bool bAdjustWeight = true);

	/**
	 * Splits an existing stack into two separate items
	 * @param ItemIn - Item stack to split
	 * @param AmountToSplit - Quantity to split off into new stack
	 */
	void SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit);

	/**
	 * Uses an item on a specific actor
	 * @param ItemToUse - Item to use
	 * @param UserActor - Actor using the item
	 * @return Result of the use operation
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory|Use")
	EItemUseResult UseItemForActor(class UItemBase* ItemToUse, class AActor* UserActor);

	//==========================================================================
	// GETTERS & SETTERS
	//==========================================================================
	
	// Getters
	FORCEINLINE TArray<UItemBase*> GetInventoryContents() const { return InventoryContents; }
	
	// Setters
	FORCEINLINE void SetSlotsCapacity(const int32 NewSlotsCapacity) { ItemSlotCount = NewSlotsCapacity; }
	FORCEINLINE void SetWeightCapacity(const float NewWeightCapacity) { MaxWeightCapacity = NewWeightCapacity; }

	//==========================================================================
	// PUBLIC PROPERTIES
	//==========================================================================
	
	// Inventory update delegate
	FOnInventoryUpdated InventoryWasUpdated;

	// Inventory capacity properties
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	float InventoryTotalWeight;
	
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 ItemSlotCount;
	
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	float MaxWeightCapacity;

protected:
	//==========================================================================
	// PROTECTED FUNCTIONS
	//==========================================================================
	virtual void BeginPlay() override;

	/**
	 * Handles adding non-stackable items to inventory
	 * @param InputItem - Non-stackable item to add
	 * @return Result of the add operation
	 */
	FItemAddResult HandleNonStackableItems(const TObjectPtr<UItemBase>& InputItem);

	/**
	 * Handles adding stackable items to inventory
	 * @param ItemIn - Stackable item to add
	 * @param RequestedAddAmount - Quantity to add
	 * @return Actual amount added
	 */
	int32 HandleStackableItems(const TObjectPtr<UItemBase>& ItemIn, int32 RequestedAddAmount);

	/**
	 * Calculates how much of an item can be added based on weight capacity
	 * @param ItemIn - Item to check
	 * @param RequestedAddAmount - Desired quantity to add
	 * @return Actual amount that can be added
	 */
	int32 CalculateWeightAddAmount(const TObjectPtr<UItemBase>& ItemIn, int32 RequestedAddAmount) const;

	/**
	 * Calculates how many items are needed to complete a stack
	 * @param StackableItem - Stack to check
	 * @param RequestedAddAmount - Desired quantity to add
	 * @return Number needed to complete stack
	 */
	int32 CalculateNumberForFullStack(const TObjectPtr<UItemBase>& StackableItem, int32 RequestedAddAmount) const;

	/**
	 * Adds a new item to the inventory
	 * @param Item - Item to add
	 * @param AmountToAdd - Quantity to add
	 */
	void AddNewItem(const TObjectPtr<UItemBase>& Item, const int32 AmountToAdd);

	//==========================================================================
	// PROTECTED PROPERTIES
	//==========================================================================
	
	// Inventory contents array
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<UItemBase>> InventoryContents;
};