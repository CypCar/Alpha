#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LootRowWidget.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UTextBlock;
struct FInteractableData;

//==========================================================================
// CLASS: ULootRowWidget
//==========================================================================
UCLASS()
class ALPHA_API ULootRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//==========================================================================
	// PUBLIC FUNCTIONS
	//==========================================================================
	void Setup(const FInteractableData& Data);

protected:
	//==========================================================================
	// PROTECTED PROPERTIES
	//==========================================================================
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;
    
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuantityText;
};