#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ScoreWidget.generated.h"

//==========================================================================
// CLASS: UScoreWidget
//==========================================================================
UCLASS()
class ALPHA_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//==========================================================================
	// PUBLIC FUNCTIONS
	//==========================================================================
	void NativeConstruct() override;

	//==========================================================================
	// PUBLIC PROPERTIES
	//==========================================================================
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ScorePoints;

protected:
	//==========================================================================
	// PROTECTED FUNCTIONS
	//==========================================================================
	UFUNCTION()
	void OnResChanged(FGameplayTag Resource, int32 NewQuantity);
};