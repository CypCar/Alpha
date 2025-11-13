#include "UserInterface/HUD/StatsWidget.h"
#include "TimerManager.h"
#include "Components/Border.h"
#include "Engine/Engine.h"

//==========================================================================
// WIDGET INITIALIZATION & CLEANUP
//==========================================================================
void UStatsWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Set default color values
    HealthColor_Normal = FLinearColor(0.2f, 0.8f, 0.2f, 1.0f);
    HealthColor_Low = FLinearColor(0.8f, 0.2f, 0.2f, 1.0f);
    
    StaminaColor_Normal = FLinearColor(0.2f, 0.5f, 0.8f, 1.0f);
    StaminaColor_Low = FLinearColor(0.8f, 0.6f, 0.2f, 1.0f);
    StaminaColor_Exhausted = FLinearColor(0.8f, 0.2f, 0.2f, 1.0f);

    // Set default thresholds
    LowHealthThreshold = 0.3f;
    LowStaminaThreshold = 0.2f;

    // Hide death overlay on start
    if (DeathOverlay)
    {
        DeathOverlay->SetVisibility(ESlateVisibility::Hidden);
    }

    // Hide status text
    if (StatusText)
    {
        StatusText->SetVisibility(ESlateVisibility::Hidden);
    }
    BorderStatusText->SetVisibility(ESlateVisibility::Hidden);
    
    UpdateBarColors();
}

void UStatsWidget::NativeDestruct()
{
    // Clear timers
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(StatusTextTimer);
    }

    // Unbind delegates
    if (StatsComponent)
    {
        StatsComponent->OnHealthChanged.RemoveAll(this);
        StatsComponent->OnStaminaChanged.RemoveAll(this);
        StatsComponent->OnDeath.RemoveAll(this);
        StatsComponent->OnStaminaExhausted.RemoveAll(this);
    }

    Super::NativeDestruct();
}

//==========================================================================
// INITIALIZATION SYSTEM
//==========================================================================
void UStatsWidget::InitializeWidget(UStatsComponent* StatsComp)
{
    if (!StatsComp) return;

    StatsComponent = StatsComp;

    // Bind delegates
    StatsComponent->OnHealthChanged.AddDynamic(this, &UStatsWidget::UpdateHealthBar);
    StatsComponent->OnStaminaChanged.AddDynamic(this, &UStatsWidget::UpdateStaminaBar);
    StatsComponent->OnDeath.AddDynamic(this, &UStatsWidget::OnDeath);
    StatsComponent->OnStaminaExhausted.AddDynamic(this, &UStatsWidget::OnStaminaExhausted);

    // Initialize starting values
    UpdateHealthDisplay();
    UpdateStaminaDisplay();
    UpdateBarColors();
}

//==========================================================================
// STATS UPDATE HANDLERS
//==========================================================================
void UStatsWidget::UpdateHealthBar(float CurrentHealth, float Delta)
{
    if (!StatsComponent) return;
    
    UpdateHealthDisplay();
    
    // Show damage text if damage was taken
    if (Delta < 0)
    {
        ShowDamageText(FMath::Abs(Delta));
    }
    
    UpdateBarColors();
}

void UStatsWidget::UpdateStaminaBar(float CurrentStamina, float Delta)
{
    if (!StatsComponent) return;
    
    UpdateStaminaDisplay();
    UpdateBarColors();
}

//==========================================================================
// EVENT HANDLERS
//==========================================================================
void UStatsWidget::OnDeath(AActor* DeadActor)
{
    // Show death overlay
    if (DeathOverlay)
    {
        DeathOverlay->SetVisibility(ESlateVisibility::Visible);
    }

    // Hide normal statistics
    if (HealthBar) HealthBar->SetVisibility(ESlateVisibility::Hidden);
    if (StaminaBar) StaminaBar->SetVisibility(ESlateVisibility::Hidden);
    if (HealthText) HealthText->SetVisibility(ESlateVisibility::Hidden);
    if (StaminaText) StaminaText->SetVisibility(ESlateVisibility::Hidden);

    // Show death status
    if (StatusText)
    {
        StatusText->SetText(FText::FromString("DEAD"));
        StatusText->SetVisibility(ESlateVisibility::Visible);
        BorderStatusText->SetVisibility(ESlateVisibility::Visible);
    }
}

void UStatsWidget::OnStaminaExhausted()
{
    if (!StatusText) return;

    // Show exhaustion status
    StatusText->SetText(FText::FromString("EXHAUSTED!"));
    StatusText->SetVisibility(ESlateVisibility::Visible);

    // Set timer to hide text
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(StatusTextTimer, this, &UStatsWidget::ClearStatusText, 3.0f, false);
    }
}

//==========================================================================
// VISUAL EFFECTS SYSTEM
//==========================================================================
void UStatsWidget::ShowDamageText(float DamageAmount)
{
    if (!StatusText) return;

    FString DamageString = FString::Printf(TEXT("-%.0f"), DamageAmount);
    StatusText->SetText(FText::FromString(DamageString));
    StatusText->SetVisibility(ESlateVisibility::Visible);

    // Set timer to hide text
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(StatusTextTimer, this, &UStatsWidget::ClearStatusText, 2.0f, false);
    }
}

void UStatsWidget::ClearStatusText()
{
    if (StatusText && StatusText->GetText().ToString() != "DEAD")
    {
        StatusText->SetVisibility(ESlateVisibility::Hidden);
    }
}

//==========================================================================
// DISPLAY UPDATE SYSTEM
//==========================================================================
void UStatsWidget::UpdateHealthDisplay()
{
    if (!StatsComponent || !HealthBar || !HealthText) return;

    float CurrentHealth = StatsComponent->GetCurrentHealth();
    float MaxHealth = StatsComponent->GetMaxHealth();
    
    // Update progress bar
    float HealthPercentage = MaxHealth > 0 ? CurrentHealth / MaxHealth : 0;
    HealthBar->SetPercent(HealthPercentage);

    // Update text
    FString HealthString = FString::Printf(TEXT("%.0f / %.0f"), CurrentHealth, MaxHealth);
    HealthText->SetText(FText::FromString(HealthString));
}

void UStatsWidget::UpdateStaminaDisplay()
{
    if (!StatsComponent || !StaminaBar || !StaminaText) return;

    float CurrentStamina = StatsComponent->GetCurrentStamina();
    float MaxStamina = StatsComponent->GetMaxStamina();
    
    // Update progress bar
    float StaminaPercentage = MaxStamina > 0 ? CurrentStamina / MaxStamina : 0;
    StaminaBar->SetPercent(StaminaPercentage);

    // Update text
    FString StaminaString = FString::Printf(TEXT("%.0f / %.0f"), CurrentStamina, MaxStamina);
    StaminaText->SetText(FText::FromString(StaminaString));
}

void UStatsWidget::UpdateBarColors()
{
    if (!StatsComponent) return;

    // Update health color
    if (HealthBar)
    {
        float HealthPercentage = StatsComponent->GetHealthPercentage();
        FLinearColor HealthColor = HealthPercentage <= LowHealthThreshold ? HealthColor_Low : HealthColor_Normal;
        HealthBar->SetFillColorAndOpacity(HealthColor);
    }

    // Update stamina color
    if (StaminaBar)
    {
        float StaminaPercentage = StatsComponent->GetStaminaPercentage();
        FLinearColor StaminaColor = StaminaColor_Normal;
        
        if (StatsComponent->IsExhausted())
        {
            StaminaColor = StaminaColor_Exhausted;
        }
        else if (StaminaPercentage <= LowStaminaThreshold)
        {
            StaminaColor = StaminaColor_Low;
        }

        StaminaBar->SetFillColorAndOpacity(StaminaColor);
    }
}