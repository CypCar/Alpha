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
	void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ScorePoints;

protected:

	UFUNCTION()
	void OnResChanged(FGameplayTag Resource, int32 NewQuantity);
};
