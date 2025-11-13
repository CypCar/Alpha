#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LootWindowWidget.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UVerticalBox;
class ULootRowWidget;
struct FInteractableData;
class AAlphaCharacter;

//==========================================================================
// CLASS: ULootWindowWidget
//==========================================================================
UCLASS()
class ALPHA_API ULootWindowWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    //==========================================================================
    // PUBLIC FUNCTIONS
    //==========================================================================
    void PushLoot(const FInteractableData& Data);

    UFUNCTION(BlueprintCallable, Category = "Loot")
    void BindToCharacter(AAlphaCharacter* Character);

    UFUNCTION(BlueprintCallable, Category = "Loot")
    void UnbindFromCharacter();

    //==========================================================================
    // PUBLIC PROPERTIES
    //==========================================================================
    
    // Display Configuration
    UPROPERTY(EditDefaultsOnly, Category = "Loot")
    int32 MaxVisibleEntries = 5;

    UPROPERTY(EditDefaultsOnly, Category = "Loot")
    float EntryLifetime = 5.f;

    UPROPERTY(EditDefaultsOnly, Category = "Loot")
    TSubclassOf<ULootRowWidget> RowClass;

protected:
    //==========================================================================
    // PROTECTED FUNCTIONS
    //==========================================================================
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    UFUNCTION()
    void OnLootPickedUp(const FInteractableData& LootData);

    //==========================================================================
    // PROTECTED PROPERTIES
    //==========================================================================
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* LootListBox = nullptr;

private:
    //==========================================================================
    // PRIVATE FUNCTIONS
    //==========================================================================
    void ScheduleRemoval(ULootRowWidget* Row);

    //==========================================================================
    // PRIVATE PROPERTIES
    //==========================================================================
    UPROPERTY()
    AAlphaCharacter* BoundCharacter = nullptr;

    // Store timers per row for safe cancellation
    TMap<TWeakObjectPtr<ULootRowWidget>, FTimerHandle> RowTimers;
};