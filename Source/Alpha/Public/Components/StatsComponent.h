#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"

// Delegaty dla zdarzeń
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChanged, float, NewStamina, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, AActor*, KilledActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaExhausted);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ALPHA_API UStatsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UStatsComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // === ZDROWIE ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    float CurrentHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    bool bCanRegenerateHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "bCanRegenerateHealth"))
    float HealthRegenRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "bCanRegenerateHealth"))
    float HealthRegenDelay;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    bool bIsDead;

    // === STAMINA ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
    float MaxStamina;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina")
    float CurrentStamina;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
    float StaminaRegenRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
    float StaminaDrainRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
    float StaminaRegenDelay;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina")
    bool bIsSprinting;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina")
    bool bIsExhausted;

    // Timery
    FTimerHandle HealthRegenTimer;
    FTimerHandle StaminaRegenTimer;
    FTimerHandle StaminaDelayTimer;

    // Zmienne wewnętrzne
    float LastStaminaUseTime;

public:
    // === FUNKCJE ZDROWIA ===
    UFUNCTION(BlueprintCallable, Category = "Health")
    void TakeDamage(float DamageAmount, AController* Instigator = nullptr);

    UFUNCTION(BlueprintCallable, Category = "Health")
    void Heal(float HealAmount);

    UFUNCTION(BlueprintCallable, Category = "Health")
    void Kill();

    UFUNCTION(BlueprintCallable, Category = "Health")
    void Revive(float ReviveHealth = 0.0f);

    UFUNCTION(BlueprintCallable, Category = "Health")
    void SetMaxHealth(float NewMaxHealth, bool bResetCurrent = false);

    UFUNCTION(BlueprintPure, Category = "Health")
    float GetHealthPercentage() const;

    UFUNCTION(BlueprintPure, Category = "Health")
    bool IsAlive() const { return !bIsDead; }

    // === FUNKCJE STAMINY ===
    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void StartSprinting();

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void StopSprinting();

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    bool CanSprint() const;

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    bool ConsumeStamina(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void SetMaxStamina(float NewMaxStamina, bool bResetCurrent = false);

    UFUNCTION(BlueprintPure, Category = "Stamina")
    float GetStaminaPercentage() const;

    UFUNCTION(BlueprintPure, Category = "Stamina")
    bool HasStamina(float RequiredAmount = 0.0f) const;

    // === GETTERY ===
    UFUNCTION(BlueprintPure, Category = "Health")
    FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

    UFUNCTION(BlueprintPure, Category = "Health")
    FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

    UFUNCTION(BlueprintPure, Category = "Stamina")
    FORCEINLINE float GetCurrentStamina() const { return CurrentStamina; }

    UFUNCTION(BlueprintPure, Category = "Stamina")
    FORCEINLINE float GetMaxStamina() const { return MaxStamina; }

    // === DELEGATY ===
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnHealthChanged OnHealthChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnStaminaChanged OnStaminaChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDeath OnDeath;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnStaminaExhausted OnStaminaExhausted;

protected:
    // Funkcje wewnętrzne
    void HandleDeath();
    void StartHealthRegeneration();
    void StopHealthRegeneration();
    void RegenerateHealth();
    void StartStaminaRegeneration();
    void StopStaminaRegeneration();
    void RegenerateStamina();
    void UpdateStamina(float DeltaTime);
};