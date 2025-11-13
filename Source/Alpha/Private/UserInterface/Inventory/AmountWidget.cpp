#include "UserInterface/Inventory/AmountWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Items/ItemBase.h"

//==========================================================================
// WIDGET INITIALIZATION
//==========================================================================
void UAmountWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    // Bind Button Events
    Minus5Button->OnClicked.AddDynamic(this, &UAmountWidget::Minus5Clicked);
    Minus1Button->OnClicked.AddDynamic(this, &UAmountWidget::Minus1Clicked);
    Plus1Button->OnClicked.AddDynamic(this, &UAmountWidget::Plus1Clicked);
    Plus5Button->OnClicked.AddDynamic(this, &UAmountWidget::Plus5Clicked);
    ConfirmButton->OnClicked.AddDynamic(this, &UAmountWidget::ConfirmClicked);
    CancelButton->OnClicked.AddDynamic(this, &UAmountWidget::CancelClicked);

    // Initialize Default Values
    AmountValue = 1;
    AmountText->SetText(FText::AsNumber(AmountValue));
}

//==========================================================================
// TEXT MANAGEMENT
//==========================================================================
void UAmountWidget::SetHeaderText(const FText& InputText) const
{
    HeaderText->SetText(InputText);
}

//==========================================================================
// AMOUNT ADJUSTMENT HANDLERS
//==========================================================================
void UAmountWidget::Minus5Clicked()
{
    AmountValue -= 5;
    AmountValue = FMath::Max(1, AmountValue);
    AmountText->SetText(FText::AsNumber(AmountValue));
}

void UAmountWidget::Minus1Clicked()
{
    AmountValue -= 1;
    AmountValue = FMath::Max(1, AmountValue);
    AmountText->SetText(FText::AsNumber(AmountValue));
}

void UAmountWidget::Plus1Clicked()
{
    AmountValue += 1;
    AmountValue = FMath::Min(AmountValue, ItemReference->Quantity - 1);
    AmountText->SetText(FText::AsNumber(AmountValue));
}

void UAmountWidget::Plus5Clicked()
{
    AmountValue += 5;
    AmountValue = FMath::Min(AmountValue, ItemReference->Quantity - 1);
    AmountText->SetText(FText::AsNumber(AmountValue));
}

//==========================================================================
// ACTION BUTTON HANDLERS
//==========================================================================
void UAmountWidget::ConfirmClicked()
{
    if (OnValueConfirm.ExecuteIfBound(AmountValue))
    {
        UE_LOG(LogTemp, Warning, TEXT("%s: OnValueConfirm delegate executed successfully, param value = %d."),
            *FString(__FUNCTION__),
            AmountValue);
    }
    CloseAmountWidget();
}

void UAmountWidget::CancelClicked()
{
    CloseAmountWidget();
}

//==========================================================================
// WIDGET MANAGEMENT
//==========================================================================
void UAmountWidget::CloseAmountWidget()
{
    // Reset Values
    AmountValue = 1;
    ItemReference = nullptr;
    AmountText->SetText(FText::AsNumber(AmountValue));
    
    // Hide Widget
    this->SetVisibility(ESlateVisibility::Collapsed);
}