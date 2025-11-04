#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LootRowWidget.generated.h"

class UTextBlock;
struct FInteractableData;

UCLASS()
class ALPHA_API ULootRowWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//==========================================================================
	//FUNCTIONS
	//==========================================================================
	void Setup(const FInteractableData& Data);

protected:
	//==========================================================================
	//PROPERTIES & VARIABELS
	//==========================================================================
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NameText;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* QuantityText;
};


