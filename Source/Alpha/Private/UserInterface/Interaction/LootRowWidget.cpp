#include "UserInterface/Interaction/LootRowWidget.h"
#include "Components/TextBlock.h"
#include "Interfaces/InteractionInterface.h"

//==========================================================================
// LOOT ROW SETUP
//==========================================================================
void ULootRowWidget::Setup(const FInteractableData& Data)
{
	// Validate widget bindings
	if (!NameText || !QuantityText) return;

	// Set item name text
	NameText->SetText(Data.Name);

	// Format and set quantity text with localization support
	FFormatOrderedArguments Args; 
	Args.Add(Data.Quantity);
	QuantityText->SetText(FText::Format(NSLOCTEXT("Loot", "QtyFmt", "x{0}"), Args));
}