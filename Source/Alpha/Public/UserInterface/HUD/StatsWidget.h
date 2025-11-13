#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/StatsComponent.h"
#include "StatsWidget.generated.h"

//==========================================================================
// CLASS: UStatsWidget
//==========================================================================
UCLASS()
class ALPHA_API UStatsWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    //==========================================================================
    // PUBLIC FUNCTIONS
    //==========================================================================
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void InitializeWidget(UStatsComponent* StatsComp);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void UpdateHealthBar(float CurrentHealth, float Delta);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void UpdateStaminaBar(float CurrentStamina, float Delta);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void OnDeath(AActor* DeadActor);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void OnStaminaExhausted();

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void ShowDamageText(float DamageAmount);

protected:
    //==========================================================================
    // PROTECTED FUNCTIONS
    //==========================================================================
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    //==========================================================================
    // PROTECTED PROPERTIES
    //==========================================================================
    
    // Widget Bindings
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthBar;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* StaminaBar;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* HealthText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* StaminaText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* StatusText;

    UPROPERTY(meta = (BindWidget))
    UBorder* BorderStatusText;
    
    UPROPERTY(meta = (BindWidget))
    UWidget* DeathOverlay;

    // Appearance Settings
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    FLinearColor HealthColor_Normal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    FLinearColor HealthColor_Low;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    FLinearColor StaminaColor_Normal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    FLinearColor StaminaColor_Low;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    FLinearColor StaminaColor_Exhausted;

    // Threshold Settings
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thresholds")
    float LowHealthThreshold;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thresholds")
    float LowStaminaThreshold;

private:
    //==========================================================================
    // PRIVATE FUNCTIONS
    //==========================================================================
    void ClearStatusText();
    void UpdateBarColors();
    void UpdateHealthDisplay();
    void UpdateStaminaDisplay();

    //==========================================================================
    // PRIVATE PROPERTIES
    //==========================================================================
    UPROPERTY()
    UStatsComponent* StatsComponent;

    FTimerHandle StatusTextTimer;
};