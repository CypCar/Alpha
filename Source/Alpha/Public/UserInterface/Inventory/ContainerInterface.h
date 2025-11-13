#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/InteractionInterface.h"
#include "ContainerInterface.generated.h"

//==========================================================================
// DELEGATES
//==========================================================================
DECLARE_DELEGATE_OneParam(FCloseContainerInterface, bool)

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class AContainer;
class UInventoryPanel;
class UButton;
class AAlphaCharacter;
class UItemBase;

//==========================================================================
// CLASS: UContainerInterface
//==========================================================================
UCLASS()
class ALPHA_API UContainerInterface : public UUserWidget
{
    GENERATED_BODY()

public:
    //==========================================================================
    // PUBLIC FUNCTIONS
    //==========================================================================
    void LinkContainerInterface(AContainer* InContainer);
    void ClearTargetContainer();
    
    UFUNCTION()
    void HideContainerInterface();

    UFUNCTION(BlueprintPure, Category = "Container")
    AContainer* GetTargetContainer() const { return TargetContainer.Get(); }

    UFUNCTION(BlueprintCallable, Category = "Container|Actions")
    void LootAllItems();

    //==========================================================================
    // PUBLIC PROPERTIES & DELEGATES
    //==========================================================================
    FCloseContainerInterface CloseContainerInterface;

    //==========================================================================
    // PUBLIC HELPER FUNCTIONS
    //==========================================================================
    bool IsLinkedToContainer(AContainer* InContainer) const
    {
        return TargetContainer == InContainer;
    }

protected:
    //==========================================================================
    // PROTECTED FUNCTIONS
    //==========================================================================
    virtual void NativeOnInitialized() override;
    virtual void NativeDestruct() override;

    //==========================================================================
    // PROTECTED PROPERTIES
    //==========================================================================
    
    // Widget Bindings
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UInventoryPanel> ContainerInventoryPanel = nullptr;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> LootAllButton = nullptr;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> CloseButton = nullptr;

private:
    //==========================================================================
    // PRIVATE FUNCTIONS
    //==========================================================================
    /** Loot single item from container */
    void LootSingleItem(UItemBase* Item);
    
    /** Create loot notification data from item */
    FInteractableData CreateLootDataFromItem(UItemBase* Item, int32 Quantity) const;

    //==========================================================================
    // PRIVATE PROPERTIES
    //==========================================================================
    UPROPERTY()
    TObjectPtr<AContainer> TargetContainer = nullptr;

    UPROPERTY()
    TObjectPtr<AAlphaCharacter> PlayerCharacter = nullptr;
};