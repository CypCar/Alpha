// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interfaces/InteractionInterface.h"  
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AlphaHUD.generated.h"

struct FInteractableData;
struct FAddedItemInfo;
class UMainMenu;
class UInteractionWidget;
class ULootWindowWidget;  

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

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<ULootWindowWidget> LootWidgetClass;

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

	void EnqueueLoot(const FInteractableData& InteractableData);



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

	UPROPERTY()
	ULootWindowWidget* LootWidget;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	float LootDisplaySeconds = 5.f;
	
	//==========================================================================
	//FUNCTIONS
	//==========================================================================
	virtual void BeginPlay() override;

private:
	
	TArray<FInteractableData> LootQueue;
	bool bLootVisible = false;

	FTimerHandle LootTimer;
};
