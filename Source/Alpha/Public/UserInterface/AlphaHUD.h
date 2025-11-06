#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AlphaHUD.generated.h"

class ULootWindowWidget;
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

	
	/** Pokaż interfejs kontenera */
	UFUNCTION(BlueprintCallable, Category="HUD|Container")
	void ShowContainerInterface(AContainer* TargetContainer = nullptr);

	/** Ukryj interfejs kontenera */
	UFUNCTION(BlueprintCallable, Category="HUD|Container")
	void HideContainerInterface(bool bSuccess = true);

	/** Ustaw target kontenera */
	UFUNCTION(BlueprintCallable, Category="HUD|Container")
	void SetTargetContainer(AContainer* TargetContainer);
	
	UFUNCTION(BlueprintCallable, Category="HUD|Container")
	void ClearTargetContainer();

	UFUNCTION(BlueprintPure, Category="HUD|Container")
	AContainer* GetCurrentContainer() const;

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
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<ULootWindowWidget> LootWindowWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UMainMenu> MainMenuWidget;

	UPROPERTY()
	TObjectPtr<UInteractionWidget> InteractionWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> CrosshairWidget;

	UPROPERTY()
	TObjectPtr<ULootWindowWidget> LootWindowWidget;

	//======================================================================================
	// FUNCTIONS
	//======================================================================================
	virtual void BeginPlay() override;
	void CreateGameWidgets();

private:
	UPROPERTY()
	TObjectPtr<UContainerInterface> ContainerInterface = nullptr;
	UPROPERTY()
	bool bContainerInterfaceManuallyOpened = false;
};
