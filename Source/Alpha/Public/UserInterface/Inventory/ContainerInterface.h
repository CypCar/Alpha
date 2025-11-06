#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/InteractionInterface.h"
#include "ContainerInterface.generated.h"

DECLARE_DELEGATE_OneParam(FCloseContainerInterface, bool)

class AContainer;
class UInventoryPanel;
class UButton;
class AAlphaCharacter;
class UItemBase;

UCLASS()
class ALPHA_API UContainerInterface : public UUserWidget
{
	GENERATED_BODY()

public:
	FCloseContainerInterface CloseContainerInterface;

	void LinkContainerInterface(AContainer* InContainer);
	void ClearTargetContainer();

	UFUNCTION()
	void HideContainerInterface();

	// ⇣ NOWE:
	UFUNCTION(BlueprintPure, Category="Container")
	AContainer* GetTargetContainer() const { return TargetContainer.Get(); }

	bool IsLinkedToContainer(AContainer* InContainer) const
	{
		return TargetContainer == InContainer;
	}

	/** Lootuj wszystkie przedmioty z kontenera */
	UFUNCTION(BlueprintCallable, Category="Container|Actions")
	void LootAllItems();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UInventoryPanel> ContainerInventoryPanel = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> LootAllButton = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> CloseButton = nullptr;

private:
	/** Lootuj pojedynczy przedmiot */
	void LootSingleItem(UItemBase* Item);
    
	/** Stwórz dane powiadomienia z przedmiotu */
	FInteractableData CreateLootDataFromItem(UItemBase* Item, int32 Quantity) const;

	UPROPERTY()
	TObjectPtr<AContainer> TargetContainer = nullptr;

	UPROPERTY()
	TObjectPtr<AAlphaCharacter> PlayerCharacter = nullptr;
};