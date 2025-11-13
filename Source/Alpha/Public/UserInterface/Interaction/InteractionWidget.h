#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class AAlphaCharacter;
class UTextBlock;
class UProgressBar;
struct FInteractableData;

//==========================================================================
// CLASS: UInteractionWidget
//==========================================================================
UCLASS()
class ALPHA_API UInteractionWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    //==========================================================================
    // PUBLIC FUNCTIONS
    //==========================================================================
    void UpdateWidget(const FInteractableData* InteractableData) const;

    //==========================================================================
    // PUBLIC PROPERTIES
    //==========================================================================
    UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Timed Interactions")
    TObjectPtr<UProgressBar> InteractionProgressBar;

protected:
    //==========================================================================
    // PROTECTED FUNCTIONS
    //==========================================================================
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;

    //==========================================================================
    // PROTECTED PROPERTIES
    //==========================================================================
    UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
    TObjectPtr<UTextBlock> KeyPressText;

    UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
    TObjectPtr<UTextBlock> ActionText;

    UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
    TObjectPtr<UTextBlock> NameText;

    UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
    TObjectPtr<UTextBlock> QuantityText;
};