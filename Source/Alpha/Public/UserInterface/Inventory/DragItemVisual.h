#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragItemVisual.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UBorder;
class UTextBlock;
class UImage;

//==========================================================================
// CLASS: UDragItemVisual
//==========================================================================
UCLASS()
class ALPHA_API UDragItemVisual : public UUserWidget
{
	GENERATED_BODY()

public:
	//==========================================================================
	// PROPERTIES
	//==========================================================================
	UPROPERTY(VisibleAnywhere, Category = "Drag Item Visual", meta = (BindWidget))
	TObjectPtr<UBorder> ItemBorder;

	UPROPERTY(VisibleAnywhere, Category = "Drag Item Visual", meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(VisibleAnywhere, Category = "Drag Item Visual", meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemQuantity;
};