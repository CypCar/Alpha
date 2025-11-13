#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Interfaces/InteractionInterface.h"
#include "Pickup.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UDataTable;
class UItemBase;
class ULootWindowWidget;

//==========================================================================
// CLASS: APickup
//==========================================================================
UCLASS()
class ALPHA_API APickup : public AActor, public IInteractionInterface
{
    GENERATED_BODY()

public:
    //==========================================================================
    // CONSTRUCTOR & PUBLIC FUNCTIONS
    //==========================================================================
    APickup();

    // Initialization
    void InitializePickup(const int32 InQuantity);
    void InitializeDrop(const TObjectPtr<UItemBase>& ItemToDrop);

    // Getters
    FORCEINLINE UItemBase* GetItemData() const { return ItemReference; }

    // Interaction Interface
    virtual void BeginFocus() override;
    virtual void EndFocus() override;

protected:
    //==========================================================================
    // PROTECTED FUNCTIONS
    //==========================================================================
    virtual void BeginPlay() override;
    virtual void Interact(AAlphaCharacter* PlayerCharacter) override;

    // Internal Functions
    void UpdateInteractableData();
    void TakePickup(const AAlphaCharacter* Taker);

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

    //==========================================================================
    // PROTECTED PROPERTIES
    //==========================================================================
    
    // Components
    UPROPERTY(VisibleAnywhere, Category = "Pickup | Components")
    UStaticMeshComponent* PickupMesh;

    // Item Data
    UPROPERTY(VisibleAnywhere, Category = "Pickup | Item Reference")
    TObjectPtr<UItemBase> ItemReference;

    // Initialization
    UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
    int32 ItemQuantity;

    UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
    FDataTableRowHandle ItemRowHandle;
};