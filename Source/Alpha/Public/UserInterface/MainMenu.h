#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class AAlphaCharacter;
class UInventoryPanel;
class UContainerInterface;

UCLASS()
class ALPHA_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<AAlphaCharacter> PlayerCharacter;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UInventoryPanel> PlayerInventory;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UContainerInterface> ContainerInterface;

protected:
	void NativeOnInitialized() override;
	void NativeConstruct() override;
	bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
