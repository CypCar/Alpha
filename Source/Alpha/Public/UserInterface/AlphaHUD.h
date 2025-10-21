// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AlphaHUD.generated.h"

struct FInteractableData;
class UMainMenu;
class UInteractionWidget;

UCLASS()
class ALPHA_API AAlphaHUD : public AHUD
{
	GENERATED_BODY()

public:
	//==========================================================================
	//PROPERTIES & VARIABELS
	//==========================================================================

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenu> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> CrosshairWidgetClass;

	bool bIsMenuVisible;

	//==========================================================================
	//FUNCTIONS
	//==========================================================================
	
	AAlphaHUD();

	void DisplayMenu();
	void HideMenu();
	void ToggleMenu();

	void ShowCrosshair();
	void HideCrosshair();

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;


protected:
	//==========================================================================
	//PROPERTIES & VARIABELS
	//==========================================================================

	UPROPERTY()
	UMainMenu* MainMenuWidget;

	UPROPERTY()
	UInteractionWidget* InteractionWidget;

	UPROPERTY()
	UUserWidget* CrosshairWidget;

	//==========================================================================
	//FUNCTIONS
	//==========================================================================

	virtual void BeginPlay() override;
};
