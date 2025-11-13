#include "UserInterface/HUD/StatsWidget.h"
#include "TimerManager.h"
#include "Components/Border.h"
#include "Engine/Engine.h"

void UStatsWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Ustaw domyślne wartości
    HealthColor_Normal = FLinearColor(0.2f, 0.8f, 0.2f, 1.0f); // Zielony
    HealthColor_Low = FLinearColor(0.8f, 0.2f, 0.2f, 1.0f);   // Czerwony
    
    StaminaColor_Normal = FLinearColor(0.2f, 0.5f, 0.8f, 1.0f);  // Niebieski
    StaminaColor_Low = FLinearColor(0.8f, 0.6f, 0.2f, 1.0f);     // Żółty
    StaminaColor_Exhausted = FLinearColor(0.8f, 0.2f, 0.2f, 1.0f); // Czerwony

    LowHealthThreshold = 0.3f;
    LowStaminaThreshold = 0.2f;

    // Ukryj overlay śmierci na start
    if (DeathOverlay)
    {
        DeathOverlay->SetVisibility(ESlateVisibility::Hidden);
    }

    // Ukryj status text
    if (StatusText)
    {
        StatusText->SetVisibility(ESlateVisibility::Hidden);
    }
    BorderStatusText->SetVisibility(ESlateVisibility::Hidden);
    UpdateBarColors();
}

void UStatsWidget::NativeDestruct()
{
    // Wyczyść timer
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(StatusTextTimer);
    }

    // Odepnij delegaty
    if (StatsComponent)
    {
        StatsComponent->OnHealthChanged.RemoveAll(this);
        StatsComponent->OnStaminaChanged.RemoveAll(this);
        StatsComponent->OnDeath.RemoveAll(this);
        StatsComponent->OnStaminaExhausted.RemoveAll(this);
    }

    Super::NativeDestruct();
}

void UStatsWidget::InitializeWidget(UStatsComponent* StatsComp)
{
    if (!StatsComp) return;

    StatsComponent = StatsComp;

    // Podepnij delegaty
    StatsComponent->OnHealthChanged.AddDynamic(this, &UStatsWidget::UpdateHealthBar);
    StatsComponent->OnStaminaChanged.AddDynamic(this, &UStatsWidget::UpdateStaminaBar);
    StatsComponent->OnDeath.AddDynamic(this, &UStatsWidget::OnDeath);
    StatsComponent->OnStaminaExhausted.AddDynamic(this, &UStatsWidget::OnStaminaExhausted);

    // Inicjalizuj wartości początkowe - WYWOŁUJEMY UPDATE BAR COLORS OD RAZU
    UpdateHealthDisplay();
    UpdateStaminaDisplay();
    UpdateBarColors(); // DODANE: Aktualizacja kolorów na start
}

void UStatsWidget::UpdateHealthBar(float CurrentHealth, float Delta)
{
    if (!StatsComponent) return;
    
    UpdateHealthDisplay();
    
    // Jeśli otrzymano obrażenia, pokaż je w status text
    if (Delta < 0)
    {
        ShowDamageText(FMath::Abs(Delta));
    }
    
    UpdateBarColors(); // DODANE: Aktualizacja kolorów po zmianie zdrowia
}

void UStatsWidget::UpdateStaminaBar(float CurrentStamina, float Delta)
{
    if (!StatsComponent) return;
    
    UpdateStaminaDisplay();
    UpdateBarColors(); // DODANE: Aktualizacja kolorów po zmianie staminy
}

void UStatsWidget::OnDeath(AActor* DeadActor)
{
    // Pokaz overlay śmierci
    if (DeathOverlay)
    {
        DeathOverlay->SetVisibility(ESlateVisibility::Visible);
    }

    // Ukryj normalne statystyki
    if (HealthBar) HealthBar->SetVisibility(ESlateVisibility::Hidden);
    if (StaminaBar) StaminaBar->SetVisibility(ESlateVisibility::Hidden);
    if (HealthText) HealthText->SetVisibility(ESlateVisibility::Hidden);
    if (StaminaText) StaminaText->SetVisibility(ESlateVisibility::Hidden);

    // Pokaz status śmierci
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

    // Pokaz status wyczerpania
    StatusText->SetText(FText::FromString("EXHAUSTED!"));
    StatusText->SetVisibility(ESlateVisibility::Visible);

    // Ustaw timer do ukrycia tekstu
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(StatusTextTimer, this, &UStatsWidget::ClearStatusText, 3.0f, false);
    }
}

void UStatsWidget::ShowDamageText(float DamageAmount)
{
    if (!StatusText) return;

    FString DamageString = FString::Printf(TEXT("-%.0f"), DamageAmount);
    StatusText->SetText(FText::FromString(DamageString));
    StatusText->SetVisibility(ESlateVisibility::Visible);

    // Ustaw timer do ukrycia tekstu
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

void UStatsWidget::UpdateHealthDisplay()
{
    if (!StatsComponent || !HealthBar || !HealthText) return;

    float CurrentHealth = StatsComponent->GetCurrentHealth();
    float MaxHealth = StatsComponent->GetMaxHealth();
    
    // Uaktualnij progress bar
    float HealthPercentage = MaxHealth > 0 ? CurrentHealth / MaxHealth : 0;
    HealthBar->SetPercent(HealthPercentage);

    // Uaktualnij tekst
    FString HealthString = FString::Printf(TEXT("%.0f / %.0f"), CurrentHealth, MaxHealth);
    HealthText->SetText(FText::FromString(HealthString));
}

void UStatsWidget::UpdateStaminaDisplay()
{
    if (!StatsComponent || !StaminaBar || !StaminaText) return;

    float CurrentStamina = StatsComponent->GetCurrentStamina();
    float MaxStamina = StatsComponent->GetMaxStamina();
    
    // Uaktualnij progress bar
    float StaminaPercentage = MaxStamina > 0 ? CurrentStamina / MaxStamina : 0;
    StaminaBar->SetPercent(StaminaPercentage);

    // Uaktualnij tekst
    FString StaminaString = FString::Printf(TEXT("%.0f / %.0f"), CurrentStamina, MaxStamina);
    StaminaText->SetText(FText::FromString(StaminaString));
}

// POPRAWIONA FUNKCJA - teraz aktualizuje kolory obu pasków
void UStatsWidget::UpdateBarColors()
{
    if (!StatsComponent) return;

    // Aktualizacja koloru zdrowia
    if (HealthBar)
    {
        float HealthPercentage = StatsComponent->GetHealthPercentage();
        FLinearColor HealthColor = HealthPercentage <= LowHealthThreshold ? HealthColor_Low : HealthColor_Normal;
        HealthBar->SetFillColorAndOpacity(HealthColor);
    }

    // Aktualizacja koloru staminy
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