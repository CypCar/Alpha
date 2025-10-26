#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "LootContainer.generated.h"

class UItemBase;
class UDataTable;

UCLASS()
class ALPHA_API ALootContainer : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	//==========================================================================
	//PROPERTIES & VARIABELS
	//==========================================================================

	//==========================================================================
	//FUNCTIONS
	//==========================================================================
	ALootContainer();

	void InitializePickup(const int32 InQuantity);
	
	// IInteractionInterface
	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	
	// Expose current interactable data like APickup
	FORCEINLINE UItemBase* GetItemData() { return ItemReference; };

protected:
	//==========================================================================
	//PROPERTIES & VARIABELS
	//==========================================================================
	UPROPERTY(VisibleAnywhere, Category = "Container | Components")
	UStaticMeshComponent* ContainerMesh;

	UPROPERTY(VisibleAnywhere, Category = "Container | Item Reference")
	UItemBase* ItemReference;
	
	UPROPERTY(EditAnywhere, Category = "Container | Behavior")
	bool bOneTimeLoot = true;
    
	UPROPERTY(EditAnywhere, Category = "Container | Behavior")
	bool bDestroyOnEmpty = false;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Container | State")
	bool bOpened = false;
    
	UPROPERTY(VisibleInstanceOnly, Category = "Container | Interaction")
	FInteractableData InstanceInteractableData;

	UPROPERTY(EditInstanceOnly, Category = "Container | Item Initialization")
	int32 ItemQuantity;

	UPROPERTY(EditInstanceOnly, Category = "Container | Item Initialization")
	FDataTableRowHandle ItemRowHandle;
	
	UPROPERTY(EditInstanceOnly, Category = "Container | UI")
	FText ContainerDisplayName;
	

	
	//==========================================================================
	//FUNCTIONS
	//==========================================================================
	virtual void BeginPlay() override;
	
	virtual void Interact(AAlphaCharacter* PlayerCharacter) override;
	
	void UpdateInteractableData();
	void TakeItems(AAlphaCharacter* Taker);
	bool IsEmpty() const;
	void MakeNonInteractableButBlocking();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
