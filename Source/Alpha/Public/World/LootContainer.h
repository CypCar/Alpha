#pragma once

// engine
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"

// game
#include "Interfaces/InteractionInterface.h"
#include "Components/InventoryComponent.h"

#include "LootContainer.generated.h"

class UStaticMeshComponent;
class UInventoryComponent;
class UItemBase;
class AAlphaCharacter;
struct FItemData;

USTRUCT(BlueprintType)
struct FContainerItemEntry
{
	GENERATED_BODY()

	// Wybór DataTable + RowName w jednym polu, jak w APickup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Container|Defaults")
	FDataTableRowHandle ItemRowHandle;

	// Ile sztuk tego itemu trafi do kontenera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Container|Defaults")
	int32 Quantity = 1;
};

UCLASS()
class ALPHA_API AContainer : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:
	//======================================================================================
	// FUNCTIONS
	//======================================================================================
	AContainer();

	// ==========================
	// IInteractionInterface
	// ==========================
	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void Interact(AAlphaCharacter* PlayerCharacter) override;
	
	/** Zwraca inventory kontenera – używane przez UContainerInterface */
	FORCEINLINE UInventoryComponent* GetContainerInventory() const { return ContainerInventory; }

	/** Dodaj gotowy UItemBase do kontenera (np. jak już masz instancję) */
	UFUNCTION(BlueprintCallable, Category="Container|Inventory")
	FItemAddResult AddItemToContainer(UItemBase* ItemToAdd);
	
	/** Dodaj item na podstawie DataTableRowHandle */
	UFUNCTION(BlueprintCallable, Category="Container|Inventory")
	FItemAddResult AddItemFromRowHandle(const FDataTableRowHandle& ItemRowHandle, int32 Quantity);

	/** Zasila kontener domyślną listą lootu (DefaultItems) */
	UFUNCTION(BlueprintCallable, Category="Container|Inventory")
	void PopulateContainerFromDefaults();

	/** Wywoływane przez UI przy zlootowaniu itemu – np. do VFX/SFX/logów */
	void NotifyItemLooted(const FInteractableData& LootData);

	/** Event do override’u w BP (partikle, dźwięk, itp.) */
	UFUNCTION(BlueprintImplementableEvent, Category="Container|Events")
	void OnItemLooted(const FText& ItemName, int32 Quantity);
	
protected:
	//======================================================================================
	// PROPERTIES & VARIABLES
	//======================================================================================

	// ==========================
	// Komponenty
	// ==========================
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Container|Components")
	TObjectPtr<UStaticMeshComponent> ContainerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Container|Components")
	TObjectPtr<UInventoryComponent> ContainerInventory;
	
	// ==========================
	// Dane interakcji
	// ==========================
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Container|Interaction")
	FText ContainerName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Container|Interaction")
	FText OpenActionText;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Container|Interaction")
	bool bIsInteractable = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Container|Interaction")
	float InteractionDuration = 0.0f;
	
	// ==========================
	// Item DataTable
	// ==========================
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Container|Defaults")
	TArray<FContainerItemEntry> DefaultItems;
	
	//======================================================================================
	// FUNCTIONS
	//======================================================================================
	virtual void BeginPlay() override;
	
	void BuildInteractableData();
};
