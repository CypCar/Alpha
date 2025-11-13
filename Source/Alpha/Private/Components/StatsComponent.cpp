#include "Components/StatsComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

//==========================================================================
// CONSTRUCTOR
//==========================================================================
UStatsComponent::UStatsComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    // Initialize Health System
    MaxHealth = 100.0f;
    CurrentHealth = MaxHealth;
    bCanRegenerateHealth = false;
    HealthRegenRate = 2.0f;
    HealthRegenDelay = 3.0f;
    bIsDead = false;
    LastDamageTime = 0.0f;

    // Initialize Stamina System
    MaxStamina = 100.0f;
    CurrentStamina = MaxStamina;
    StaminaRegenRate = 20.0f;
    StaminaDrainRate = 25.0f;
    StaminaRegenDelay = 1.0f;
    bIsSprinting = false;
    bIsExhausted = false;
    
    LastStaminaUseTime = 0.0f;
}

//==========================================================================
// BEGIN PLAY
//==========================================================================
void UStatsComponent::BeginPlay()
{
    Super::BeginPlay();
    
    // Reset to initial values
    CurrentHealth = MaxHealth;
    CurrentStamina = MaxStamina;
    bIsDead = false;
    bIsExhausted = false;
    LastDamageTime = 0.0f;
    LastStaminaUseTime = GetWorld()->GetTimeSeconds();
}

//==========================================================================
// TICK COMPONENT
//==========================================================================
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    // Update Stamina System
    UpdateStamina(DeltaTime);
    
    // Handle Health Regeneration
    if (bCanRegenerateHealth && !bIsDead && CurrentHealth < MaxHealth)
    {
        float CurrentTime = GetWorld()->GetTimeSeconds();
        if (CurrentTime - LastDamageTime >= HealthRegenDelay)
        {
            Heal(HealthRegenRate * DeltaTime);
        }
    }
}

//==========================================================================
// HEALTH SYSTEM IMPLEMENTATION
//==========================================================================
void UStatsComponent::TakeDamage(float DamageAmount, AController* Instigator)
{
    if (bIsDead || DamageAmount <= 0.0f) return;

    float OldHealth = CurrentHealth;
    CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
    
    float ActualDamage = OldHealth - CurrentHealth;
    OnHealthChanged.Broadcast(CurrentHealth, -ActualDamage);
    OnDamageTaken.Broadcast(ActualDamage);

    // Update last damage time for regeneration delay
    LastDamageTime = GetWorld()->GetTimeSeconds();

    if (CurrentHealth <= 0.0f)
    {
        HandleDeath();
    }
    
    // Play damage sound effect
    if (const AActor* OwnerActor = GetOwner())
    {
        UGameplayStatics::PlaySoundAtLocation(
            this,
            UseSound,
            OwnerActor->GetActorLocation()
        );
    }
}

void UStatsComponent::Heal(float HealAmount)
{
    if (bIsDead || HealAmount <= 0.0f) return;

    float OldHealth = CurrentHealth;
    CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
    
    float ActualHeal = CurrentHealth - OldHealth;
    OnHealthChanged.Broadcast(CurrentHealth, ActualHeal);
}

void UStatsComponent::Kill()
{
    if (bIsDead) return;

    CurrentHealth = 0.0f;
    OnHealthChanged.Broadcast(0.0f, -CurrentHealth);
    HandleDeath();
}

void UStatsComponent::Revive(float ReviveHealth)
{
    if (!bIsDead) return;

    bIsDead = false;
    CurrentHealth = FMath::Clamp(ReviveHealth > 0.0f ? ReviveHealth : MaxHealth * 0.5f, 0.0f, MaxHealth);
    CurrentStamina = MaxStamina * 0.25f; // Partial stamina on revive
    
    OnHealthChanged.Broadcast(CurrentHealth, CurrentHealth);
    OnStaminaChanged.Broadcast(CurrentStamina, CurrentStamina);
}

void UStatsComponent::SetMaxHealth(float NewMaxHealth, bool bResetCurrent)
{
    MaxHealth = FMath::Max(0.1f, NewMaxHealth);
    if (bResetCurrent)
    {
        CurrentHealth = MaxHealth;
    }
    else
    {
        CurrentHealth = FMath::Min(CurrentHealth, MaxHealth);
    }
    
    OnHealthChanged.Broadcast(CurrentHealth, 0.0f);
}

float UStatsComponent::GetHealthPercentage() const
{
    return MaxHealth > 0.0f ? CurrentHealth / MaxHealth : 0.0f;
}

void UStatsComponent::HandleDeath()
{
    bIsDead = true;
    StopSprinting();
    StopHealthRegeneration();
    StopStaminaRegeneration();
    
    OnDeath.Broadcast(GetOwner());
}

void UStatsComponent::StartHealthRegeneration()
{
    if (!bCanRegenerateHealth || bIsDead) return;
    
    GetWorld()->GetTimerManager().SetTimer(HealthRegenTimer, this, &UStatsComponent::RegenerateHealth, 0.1f, true);
}

void UStatsComponent::StopHealthRegeneration()
{
    GetWorld()->GetTimerManager().ClearTimer(HealthRegenTimer);
}

void UStatsComponent::RegenerateHealth()
{
    if (bIsDead || CurrentHealth >= MaxHealth)
    {
        StopHealthRegeneration();
        return;
    }

    Heal(HealthRegenRate * 0.1f);
}

//==========================================================================
// STAMINA SYSTEM IMPLEMENTATION
//==========================================================================
void UStatsComponent::StartSprinting()
{
    if (!CanSprint() || bIsExhausted) return;

    bIsSprinting = true;
    StopStaminaRegeneration();
}

void UStatsComponent::StopSprinting()
{
    if (!bIsSprinting) return;

    bIsSprinting = false;
    LastStaminaUseTime = GetWorld()->GetTimeSeconds();
    
    // Delay before starting stamina regeneration
    if (StaminaRegenDelay > 0.0f)
    {
        GetWorld()->GetTimerManager().SetTimer(StaminaRegenTimer, this, &UStatsComponent::StartStaminaRegeneration, StaminaRegenDelay, false);
    }
    else
    {
        StartStaminaRegeneration();
    }
}

bool UStatsComponent::CanSprint() const
{
    return !bIsDead && !bIsExhausted && CurrentStamina > 10.0f;
}

bool UStatsComponent::ConsumeStamina(float Amount)
{
    if (bIsDead || Amount <= 0.0f) return true;

    if (CurrentStamina >= Amount)
    {
        float OldStamina = CurrentStamina;
        CurrentStamina = FMath::Clamp(CurrentStamina - Amount, 0.0f, MaxStamina);
        
        float StaminaUsed = OldStamina - CurrentStamina;
        OnStaminaChanged.Broadcast(CurrentStamina, -StaminaUsed);
        
        LastStaminaUseTime = GetWorld()->GetTimeSeconds();
        StopStaminaRegeneration();
        
        // Trigger exhaustion if stamina reaches zero
        if (CurrentStamina <= 0.0f)
        {
            bIsExhausted = true;
            OnStaminaExhausted.Broadcast();
        }
        
        return true;
    }
    
    return false;
}

void UStatsComponent::SetMaxStamina(float NewMaxStamina, bool bResetCurrent)
{
    MaxStamina = FMath::Max(0.1f, NewMaxStamina);
    if (bResetCurrent)
    {
        CurrentStamina = MaxStamina;
    }
    else
    {
        CurrentStamina = FMath::Min(CurrentStamina, MaxStamina);
    }
    
    OnStaminaChanged.Broadcast(CurrentStamina, 0.0f);
}

float UStatsComponent::GetStaminaPercentage() const
{
    return MaxStamina > 0.0f ? CurrentStamina / MaxStamina : 0.0f;
}

bool UStatsComponent::HasStamina(float RequiredAmount) const
{
    return CurrentStamina >= (RequiredAmount > 0.0f ? RequiredAmount : 0.1f);
}

void UStatsComponent::UpdateStamina(float DeltaTime)
{
    if (bIsDead) return;

    // Drain stamina while sprinting
    if (bIsSprinting && CurrentStamina > 0.0f)
    {
        float OldStamina = CurrentStamina;
        CurrentStamina = FMath::Clamp(CurrentStamina - StaminaDrainRate * DeltaTime, 0.0f, MaxStamina);
        
        float StaminaDrained = OldStamina - CurrentStamina;
        if (StaminaDrained > 0.0f)
        {
            OnStaminaChanged.Broadcast(CurrentStamina, -StaminaDrained);
        }

        // Check for exhaustion
        if (CurrentStamina <= 0.0f && !bIsExhausted)
        {
            bIsExhausted = true;
            StopSprinting();
            OnStaminaExhausted.Broadcast();
        }
    }
    
    // Automatic stamina regeneration
    if (!bIsSprinting && !bIsExhausted && CurrentStamina < MaxStamina)
    {
        float CurrentTime = GetWorld()->GetTimeSeconds();
        if (CurrentTime - LastStaminaUseTime >= StaminaRegenDelay)
        {
            float OldStamina = CurrentStamina;
            CurrentStamina = FMath::Clamp(CurrentStamina + StaminaRegenRate * DeltaTime, 0.0f, MaxStamina);
            
            float StaminaGained = CurrentStamina - OldStamina;
            if (StaminaGained > 0.0f)
            {
                OnStaminaChanged.Broadcast(CurrentStamina, StaminaGained);
            }
        }
    }
    
    // Auto-recover from exhaustion
    if (bIsExhausted && CurrentStamina >= MaxStamina * 0.3f)
    {
        bIsExhausted = false;
    }
}

void UStatsComponent::StartStaminaRegeneration()
{
    if (bIsDead || bIsSprinting) return;
    
    GetWorld()->GetTimerManager().SetTimer(StaminaRegenTimer, this, &UStatsComponent::RegenerateStamina, 0.1f, true);
}

void UStatsComponent::StopStaminaRegeneration()
{
    GetWorld()->GetTimerManager().ClearTimer(StaminaRegenTimer);
}

void UStatsComponent::RegenerateStamina()
{
    if (bIsDead || bIsSprinting || CurrentStamina >= MaxStamina)
    {
        StopStaminaRegeneration();
        return;
    }

    float OldStamina = CurrentStamina;
    CurrentStamina = FMath::Clamp(CurrentStamina + StaminaRegenRate * 0.1f, 0.0f, MaxStamina);
    
    float StaminaGained = CurrentStamina - OldStamina;
    if (StaminaGained > 0.0f)
    {
        OnStaminaChanged.Broadcast(CurrentStamina, StaminaGained);
    }
}