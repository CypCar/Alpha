#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
// Engine
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"

// Game
#include "Interfaces/InteractionInterface.h"
#include "Components/InventoryComponent.h"
#include "LootContainer.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UStaticMeshComponent;
class UInventoryComponent;
class UItemBase;
class AAlphaCharacter;
struct FItemData;

//==========================================================================
// STRUCT: FContainerItemEntry
//==========================================================================
USTRUCT(BlueprintType)
struct FContainerItemEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container|Defaults")
    FDataTableRowHandle ItemRowHandle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container|Defaults")
    int32 Quantity = 1;
};

//==========================================================================
// CLASS: AContainer
//==========================================================================
UCLASS()
class ALPHA_API AContainer : public AActor, public IInteractionInterface
{
    GENERATED_BODY()

public:
    //==========================================================================
    // CONSTRUCTOR & PUBLIC FUNCTIONS
    //==========================================================================
    AContainer();

    // Interaction Interface
    virtual void BeginFocus() override;
    virtual void EndFocus() override;
    virtual void Interact(AAlphaCharacter* PlayerCharacter) override;

    // Getters
    FORCEINLINE UInventoryComponent* GetContainerInventory() const { return ContainerInventory; }

    // Inventory Management
    UFUNCTION(BlueprintCallable, Category = "Container|Inventory")
    FItemAddResult AddItemToContainer(UItemBase* ItemToAdd);

    UFUNCTION(BlueprintCallable, Category = "Container|Inventory")
    FItemAddResult AddItemFromRowHandle(const FDataTableRowHandle& ItemRowHandle, int32 Quantity);

    UFUNCTION(BlueprintCallable, Category = "Container|Inventory")
    void PopulateContainerFromDefaults();

    // Loot System
    void NotifyItemLooted(const FInteractableData& LootData);

    UFUNCTION(BlueprintImplementableEvent, Category = "Container|Events")
    void OnItemLooted(const FText& ItemName, int32 Quantity);

protected:
    //==========================================================================
    // PROTECTED FUNCTIONS
    //==========================================================================
    virtual void BeginPlay() override;
    void BuildInteractableData();

    //==========================================================================
    // PROTECTED PROPERTIES
    //==========================================================================
    
    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Container|Components")
    TObjectPtr<UStaticMeshComponent> ContainerMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Container|Components")
    TObjectPtr<UInventoryComponent> ContainerInventory;

    // Interaction Data
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Container|Interaction")
    FText ContainerName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Container|Interaction")
    FText OpenActionText;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Container|Interaction")
    bool bIsInteractable = true;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Container|Interaction")
    float InteractionDuration = 0.0f;

    // Default Items
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Container|Defaults")
    TArray<FContainerItemEntry> DefaultItems;
};