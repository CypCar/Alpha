#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/StatsComponent.h"
#include "StatsWidget.generated.h"

UCLASS()
class ALPHA_API UStatsWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    //==========================================================================
    //PROPERTIES & VARIABELS
    //==========================================================================

    //==========================================================================
    //FUNCTIONS
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
    //PROPERTIES & VARIABELS
    //==========================================================================
    // Bindowanie widgetów
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

    // Style dla różnych stanów
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

    // Progi dla kolorów ostrzegawczych
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thresholds")
    float LowHealthThreshold;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thresholds")
    float LowStaminaThreshold;
    
    //==========================================================================
    //FUNCTIONS
    //==========================================================================
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    //==========================================================================
    //PROPERTIES & VARIABELS
    //==========================================================================
    UPROPERTY()
    UStatsComponent* StatsComponent;

    // Timer dla efektów wizualnych
    FTimerHandle StatusTextTimer;
    
    //==========================================================================
    //FUNCTIONS
    //==========================================================================
    void ClearStatusText();
    void UpdateBarColors();
    void UpdateHealthDisplay();
    void UpdateStaminaDisplay();
};