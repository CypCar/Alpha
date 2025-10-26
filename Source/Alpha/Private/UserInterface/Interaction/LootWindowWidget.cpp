#include "UserInterface/Interaction/LootWindowWidget.h"
#include "UserInterface/Interaction/LootRowWidget.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "TimerManager.h"

void ULootWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Collapsed);
}

void ULootWindowWidget::PushLoot(const FInteractableData& Data)
{
	if (!LootListBox || !RowClass) { UE_LOG(LogTemp, Warning, TEXT("LootWindow: LootListBox/RowClass null")); return; }

	APlayerController* PC = GetOwningPlayer();
	ULootRowWidget* Row = PC
		? CreateWidget<ULootRowWidget>(PC, RowClass)
		: CreateWidget<ULootRowWidget>(GetWorld(), RowClass); // fallback

	if (!Row) { UE_LOG(LogTemp, Warning, TEXT("LootWindow: Create row failed (RowClass=%s)"), *GetNameSafe(*RowClass)); return; }

	Row->Setup(Data);
	LootListBox->InsertChildAt(0, Row);      // nowy NA GÓRZE
	while (LootListBox->GetChildrenCount() > MaxVisibleEntries)
	{
		if (UWidget* Last = LootListBox->GetChildAt(LootListBox->GetChildrenCount() - 1))
		{
			LootListBox->RemoveChild(Last);
		}
	}
	if (GetVisibility() != ESlateVisibility::Visible) SetVisibility(ESlateVisibility::Visible);
	ScheduleRemoval(Row);
}


void ULootWindowWidget::ScheduleRemoval(ULootRowWidget* Row)
{
	if (!Row) return;

	FTimerHandle Handle;
	FTimerDelegate Dlg;

	// użyj słabego wskaźnika, żeby nie trzymać obiektu przy życiu
	TWeakObjectPtr<ULootRowWidget> WeakRow = Row;

	Dlg.BindLambda([this, WeakRow]()
	{
		if (!LootListBox) return;

		if (WeakRow.IsValid())
		{
			LootListBox->RemoveChild(WeakRow.Get());
		}

		// schowaj cały widget, gdy nie ma żadnych wpisów
		if (LootListBox->GetChildrenCount() == 0)
		{
			SetVisibility(ESlateVisibility::Collapsed);
		}
	});

	GetWorld()->GetTimerManager().SetTimer(Handle, Dlg, EntryLifetime, false);
	RowTimers.Add(WeakRow, Handle);
}
