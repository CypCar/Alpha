#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDragDropOperation.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UItemBase;
class UInventoryComponent;

//==========================================================================
// CLASS: UItemDragDropOperation
//==========================================================================
UCLASS()
class ALPHA_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	//==========================================================================
	// PROPERTIES
	//==========================================================================
	UPROPERTY()
	TObjectPtr<UItemBase> SourceItem;
};