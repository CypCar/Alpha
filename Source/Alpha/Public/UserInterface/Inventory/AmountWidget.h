#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmountWidget.generated.h"

//==========================================================================
// DELEGATES
//==========================================================================
DECLARE_DELEGATE_OneParam(FOnValueConfirm, int32)

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UItemBase;
class UButton;
class UTextBlock;

//==========================================================================
// CLASS: UAmountWidget
//==========================================================================
UCLASS()
class ALPHA_API UAmountWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    //==========================================================================
    // PUBLIC FUNCTIONS
    //==========================================================================
    FORCEINLINE void SetItemReference(UItemBase* ItemIn) { ItemReference = ItemIn; }
    FORCEINLINE void SetHeaderText(const FText& InputText) const;

    //==========================================================================
    // PUBLIC PROPERTIES & DELEGATES
    //==========================================================================
    FOnValueConfirm OnValueConfirm;

protected:
    //==========================================================================
    // PROTECTED FUNCTIONS
    //==========================================================================
    virtual void NativeOnInitialized() override;

    // Button Handlers
    UFUNCTION()
    void Minus5Clicked();
    
    UFUNCTION()
    void Minus1Clicked();
    
    UFUNCTION()
    void Plus1Clicked();
    
    UFUNCTION()
    void Plus5Clicked();
    
    UFUNCTION()
    void ConfirmClicked();
    
    UFUNCTION()
    void CancelClicked();

    // Internal Functions
    void CloseAmountWidget();

    //==========================================================================
    // PROTECTED PROPERTIES
    //==========================================================================
    
    // State Variables
    UPROPERTY()
    int32 AmountValue;

    UPROPERTY()
    TObjectPtr<UItemBase> ItemReference;

    // Widget Bindings
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> HeaderText;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> Minus5Button;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> Minus1Button;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> Plus1Button;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> Plus5Button;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> AmountText;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> CancelButton;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> ConfirmButton;
};