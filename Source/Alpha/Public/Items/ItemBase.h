#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Data/ItemDataStructs.h"
#include "Components/InventoryComponent.h"
#include "Alpha/AlphaCharacter.h"
#include "ItemBase.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UInventoryComponent;

//==========================================================================
// CLASS: UItemBase
//==========================================================================
UCLASS()
class ALPHA_API UItemBase : public UObject
{
    GENERATED_BODY()

public:
    //==========================================================================
    // CONSTRUCTOR & PUBLIC FUNCTIONS
    //==========================================================================
    UItemBase();

    // Getters
    UFUNCTION(Category = "Item")
    FORCEINLINE UInventoryComponent* GetOwningInventory() const { return Cast<UInventoryComponent>(GetOuter()); }

    UFUNCTION(Category = "Item")
    FORCEINLINE float GetItemStackWeight() const { return Quantity * NumericData.Weight; }

    UFUNCTION(Category = "Item")
    FORCEINLINE float GetItemSingleWeight() const { return NumericData.Weight; }

    UFUNCTION(Category = "Item")
    FORCEINLINE bool IsFullItemStack() const { return Quantity == NumericData.MaxStackSize; }

    // Item Management
    UFUNCTION(Category = "Item")
    static UItemBase* CreateItemCopy(const UItemBase* ItemToCopy, UObject* NewOuter);

    UFUNCTION(Category = "Item")
    void SetQuantity(const int32 NewQuantity);

    UFUNCTION(Category = "Item")
    virtual void Use(AAlphaCharacter* PlayerCharacter);

    //==========================================================================
    // PUBLIC PROPERTIES
    //==========================================================================
    UPROPERTY(VisibleAnywhere, Category = "Item")
    FName ID;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    int32 Quantity;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    EItemType ItemType;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    EItemQuality ItemQuality;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    FItemStatistics ItemStatistics;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    FItemTextData TextData;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    FItemNumericData NumericData;

    UPROPERTY(VisibleAnywhere, Category = "Item")
    FItemAssetData AssetData;

protected:
    //==========================================================================
    // PROTECTED OPERATORS
    //==========================================================================
    bool operator==(const FName& OtherID) const
    {
        return this->ID == OtherID;
    }
};