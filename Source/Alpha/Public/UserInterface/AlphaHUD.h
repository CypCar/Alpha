#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AlphaHUD.generated.h"

class UMainMenu;
class UInteractionWidget;
class UAmountWidget;
class AContainer;
class UContainerInterface;
class AAlphaCharacter;
struct FInteractableData;

UCLASS()
class ALPHA_API AAlphaHUD : public AHUD
{
	GENERATED_BODY()

public:
	//======================================================================================
	// PROPERTIES & VARIABLES
	//======================================================================================
	bool bMainMenuOpen;
	bool bContainerInterfaceOpen;
	bool bInteractionWidgetVisible;

	//======================================================================================
	// FUNCTIONS
	//======================================================================================
	AAlphaHUD();

	bool HasAnyMenuOpen() const;

	void DisplayMenu();
	void HideMenu();
	void ToggleMenu();

	void ShowCrosshair() const;
	void HideCrosshair() const;

	void ShowInteractionWidget();
	void HideInteractionWidget();
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;
	TObjectPtr<UInteractionWidget> GetInteractionWidget() { return InteractionWidget; }

	void SetTargetContainer(AContainer* TargetContainer);
	void ClearTargetContainer();
	void ShowContainerInterface(const bool bModifyInputMode = false);
	void HideContainerInterface(const bool bModifyInputMode = false);

protected:
	//======================================================================================
	// PROPERTIES & VARIABLES
	//======================================================================================
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenu> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> CrosshairWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UContainerInterface> ContainerInterfaceClass;

	UPROPERTY()
	TObjectPtr<UMainMenu> MainMenuWidget;

	UPROPERTY()
	TObjectPtr<UInteractionWidget> InteractionWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> CrosshairWidget;

	//======================================================================================
	// FUNCTIONS
	//======================================================================================
	virtual void BeginPlay() override;

	void CreateGameWidgets();
};
