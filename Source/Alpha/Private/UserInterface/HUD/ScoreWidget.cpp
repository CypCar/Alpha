#include "UserInterface/HUD/ScoreWidget.h"
#include "GameplayTagsManager.h"
#include "Subsystems/ResourcesSubsystem.h"

//==========================================================================
// WIDGET INITIALIZATION
//==========================================================================
void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UResourcesSubsystem* Subsystem = GetWorld()->GetSubsystem<UResourcesSubsystem>();
	Subsystem->OnResourceChange.AddDynamic(this, &UScoreWidget::OnResChanged);
}

//==========================================================================
// RESOURCE EVENT HANDLER
//==========================================================================
void UScoreWidget::OnResChanged(FGameplayTag Resource, int32 NewQuantity)
{
	if (Resource == FGameplayTag::RequestGameplayTag(TEXT("Gameplay.Systems.Points.Coins")))
	{
		ScorePoints->SetText(FText::AsNumber(NewQuantity));
	}
}