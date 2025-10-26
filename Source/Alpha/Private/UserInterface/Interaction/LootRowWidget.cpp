#include "UserInterface/Interaction/LootRowWidget.h"
#include "Components/TextBlock.h"
#include "Interfaces/InteractionInterface.h"

void ULootRowWidget::Setup(const FInteractableData& Data)
{
	if (!NameText || !QuantityText) return;

	NameText->SetText(Data.Name);

	FFormatOrderedArguments Args; Args.Add(Data.Quantity);
	QuantityText->SetText(FText::Format(NSLOCTEXT("Loot", "QtyFmt", "x{0}"), Args));
}
