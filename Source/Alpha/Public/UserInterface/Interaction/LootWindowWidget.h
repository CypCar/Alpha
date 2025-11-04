#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LootWindowWidget.generated.h"

class UVerticalBox;
class ULootRowWidget;
struct FInteractableData;

UCLASS()
class ALPHA_API ULootWindowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//==========================================================================
	//PROPERTIES & VARIABELS
	//==========================================================================
	
	// Ile wpisów ma być widocznych jednocześnie (starsze usuwamy z dołu)
	UPROPERTY(EditDefaultsOnly, Category="Loot")
	int32 MaxVisibleEntries = 5;

	// Jak długo jeden wpis ma wisieć (sekundy)
	UPROPERTY(EditDefaultsOnly, Category="Loot")
	float EntryLifetime = 5.f;

	// Klasa pojedynczego wiersza
	UPROPERTY(EditDefaultsOnly, Category="Loot")
	TSubclassOf<ULootRowWidget> RowClass;
	
	//==========================================================================
	//FUNCTIONS
	//==========================================================================
	
	// Dodaj nowy wpis na górę listy
	void PushLoot(const FInteractableData& Data);

protected:
	//==========================================================================
	//PROPERTIES & VARIABELS
	//==========================================================================
	UPROPERTY(meta=(BindWidget)) UVerticalBox* LootListBox = nullptr;
	
	//==========================================================================
	//FUNCTIONS
	//==========================================================================
	virtual void NativeConstruct() override;

private:
	
	void ScheduleRemoval(ULootRowWidget* Row);

	// trzymamy timery per-wiersz żeby móc je bezpiecznie anulować
	TMap<TWeakObjectPtr<ULootRowWidget>, FTimerHandle> RowTimers;
};
