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
	// Dodaj nowy wpis na górę listy
	void PushLoot(const FInteractableData& Data);

	// Ile wpisów ma być widocznych jednocześnie (starsze usuwamy z dołu)
	UPROPERTY(EditDefaultsOnly, Category="Loot")
	int32 MaxVisibleEntries = 5;

	// Jak długo jeden wpis ma wisieć (sekundy)
	UPROPERTY(EditDefaultsOnly, Category="Loot")
	float EntryLifetime = 5.f;

	// Klasa pojedynczego wiersza
	UPROPERTY(EditDefaultsOnly, Category="Loot")
	TSubclassOf<ULootRowWidget> RowClass;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget)) UVerticalBox* LootListBox = nullptr;

private:
	void ScheduleRemoval(ULootRowWidget* Row);

	// trzymamy timery per-wiersz żeby móc je bezpiecznie anulować
	TMap<TWeakObjectPtr<ULootRowWidget>, FTimerHandle> RowTimers;
};
