#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>

#include "ScoreWidget.generated.h"


UCLASS()
class ALPHA_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//==========================================================================
	//PROPERTIES & VARIABELS
	//==========================================================================
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ScorePoints;
	
	//==========================================================================
	//FUNCTIONS
	//==========================================================================
	void NativeConstruct() override;

protected:
	//==========================================================================
	//PROPERTIES & VARIABELS
	//==========================================================================

	//==========================================================================
	//FUNCTIONS
	//==========================================================================
	UFUNCTION()
	void OnResChanged(FGameplayTag Resource, int32 NewQuantity);
};
