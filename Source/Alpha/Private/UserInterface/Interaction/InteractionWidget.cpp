#include "UserInterface/Interaction/InteractionWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Interfaces/InteractionInterface.h"

//==========================================================================
// WIDGET INITIALIZATION
//==========================================================================
void UInteractionWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void UInteractionWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Set default key press text
    KeyPressText->SetText(FText::FromString("Press"));
}

//==========================================================================
// WIDGET UPDATE SYSTEM
//==========================================================================
void UInteractionWidget::UpdateWidget(const FInteractableData* InteractableData) const
{
    switch (InteractableData->InteractableType)
    {
    // ============================= PICKUP =============================
    case EInteractableType::Pickup:
        KeyPressText->SetText(FText::FromString("Press"));
        InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);

        // Show quantity only for stackable items
        if (InteractableData->Quantity < 2)
        {
            QuantityText->SetVisibility(ESlateVisibility::Collapsed);
        }
        else
        {
            QuantityText->SetText(FText::Format(FText::FromString("x{0}"), InteractableData->Quantity));
            QuantityText->SetVisibility(ESlateVisibility::Visible);
        }
        break;

    // ============================= NPC =============================
    case EInteractableType::NonPlayerCharacter:
        QuantityText->SetVisibility(ESlateVisibility::Collapsed);
        InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
        break;

    // ============================= DEVICE =============================
    case EInteractableType::Device:
        QuantityText->SetVisibility(ESlateVisibility::Collapsed);
        
        // Show progress bar for timed interactions
        if (InteractableData->InteractionDuration > 0)
        {
            KeyPressText->SetText(FText::FromString("Hold"));
            InteractionProgressBar->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            KeyPressText->SetText(FText::FromString("Press"));
            InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
        }
        break;

    // ============================= TOGGLE =============================
    case EInteractableType::Toggle:
        QuantityText->SetVisibility(ESlateVisibility::Collapsed);
        
        // Show progress bar for timed interactions
        if (InteractableData->InteractionDuration > 0)
        {
            KeyPressText->SetText(FText::FromString("Hold"));
            InteractionProgressBar->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            KeyPressText->SetText(FText::FromString("Press"));
            InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
        }
        break;

    // ============================= CONTAINER =============================
    case EInteractableType::Container:
        KeyPressText->SetText(FText::FromString("Press"));
        QuantityText->SetVisibility(ESlateVisibility::Collapsed);
        InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
        break;

    // ============================= DEFAULT =============================
    default:
        break;
    }

    // ============================= COMMON ACTIONS =============================
    // Apply common data to all interactable types
    ActionText->SetText(InteractableData->Action);
    NameText->SetText(InteractableData->Name);
}