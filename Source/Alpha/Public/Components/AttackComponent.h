#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/DamageType.h"
#include "AttackComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackHit, AActor*, HitActor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALPHA_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//======================================================================================
	// PROPERTIES & VARIABLES
	//======================================================================================
	
	// Event when we hit something
	UPROPERTY(BlueprintAssignable, Category="Combat")
	FOnAttackHit OnAttackHit;
	
	//======================================================================================
	// FUNCTIONS
	//======================================================================================
	UAttackComponent();

	// Call to start an attack input (from Character input)
	UFUNCTION(BlueprintCallable, Category="Combat")
	void OnAttackInput();

	// Force stop combo (e.g., staggered)
	UFUNCTION(BlueprintCallable, Category="Combat")
	void StopCombo();

	// If you want to play trace independent (e.g., at specific montage notify)
	UFUNCTION(BlueprintCallable, Category="Combat")
	void PerformSwordTrace();

	// Blueprint event to call when montage anim notify triggers the actual hit moment
	UFUNCTION(BlueprintCallable, Category="Combat")
	void HandleNotify_Hit();
	
	UFUNCTION(BlueprintCallable, Category="Combat")
	void HandleNotify_ComboWindowOpen();

	UFUNCTION(BlueprintCallable, Category="Combat")
	void HandleNotify_ComboWindowClose();

	bool bComboWindowOpen = true; // na start może być true
protected:
	//======================================================================================
	// PROPERTIES & VARIABLES
	//======================================================================================

	// --- Combo config ---
	UPROPERTY(EditAnywhere, Category="Combat|Combo")
	int32 MaxCombo = 3;

	UPROPERTY(VisibleAnywhere, Category="Combat|Combo")
	int32 CurrentComboIndex = 0; // 0..MaxCombo-1

	UPROPERTY(VisibleAnywhere, Category="Combat|Combo")
	bool bIsAttacking = false;

	// Time window to accept next attack (seconds)
	UPROPERTY(EditAnywhere, Category="Combat|Combo")
	float ComboInputWindow = 0.4f;

	FTimerHandle ComboResetTimerHandle;

	// Montage and section names
	UPROPERTY(EditAnywhere, Category="Combat|Animation")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, Category="Combat|Trace")
	float TraceRadius = 15.f;

	// Socket names on Mesh for trace start/end
	UPROPERTY(EditAnywhere, Category="Combat|Trace")
	FName TraceStartSocket = "SwordSocket_Start";

	UPROPERTY(EditAnywhere, Category="Combat|Trace")
	FName TraceEndSocket = "SwordSocket_End";

	// Damage
	UPROPERTY(EditAnywhere, Category="Combat|Damage")
	float AttackDamage = 20.0f;

	UPROPERTY(EditAnywhere, Category="Combat|Damage")
	TSubclassOf<UDamageType> DamageTypeClass;

	// Sound / FX
	UPROPERTY(EditAnywhere, Category="Combat|FX")
	USoundBase* SwingSound;

	UPROPERTY(EditAnywhere, Category="Combat|FX")
	UParticleSystem* HitParticle;
	
	// Keep track of already hit actors this combo to avoid multi-hit per swing
	UPROPERTY()
	TSet<AActor*> AlreadyHitActors;

	// --- Continuous sword trace (debug + lepsze trafianie) ---
	UPROPERTY(EditAnywhere, Category="Combat|Trace")
	bool bUseContinuousTrace = true;

	UPROPERTY(EditAnywhere, Category="Combat|Trace", meta=(EditCondition="bUseContinuousTrace", ClampMin="0.005", ClampMax="0.05"))
	float TraceTickInterval = 0.015f;    // ~66 razy na sekundę

	FTimerHandle SwordTraceTimerHandle;
	
	//======================================================================================
	// FUNCTIONS
	//======================================================================================
	virtual void BeginPlay() override;

	// Helper: play montage
	void PlayAttackMontage() const;

	// Called when montage complete or we need to reset
	void ResetCombo();

	// Called after pressing attack while already attacking (queue next)
	void QueueNextAttack();

	// Whether next attack has been queued during current animation
	bool bQueuedNextAttack = false;

	// Perform the trace and apply damage
	void DoSwordTrace();

	// Internal: called by Montage Notify / Delay to actually perform trace (if you want)
	UFUNCTION()
	void MontageNotify_PerformTrace();

	UFUNCTION(BlueprintCallable, Category="Combat|Trace")
	void HandleNotify_SwordTraceStart();

	UFUNCTION(BlueprintCallable, Category="Combat|Trace")
	void HandleNotify_SwordTraceEnd();

	void SwordTraceTick();

};
