#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/DamageType.h"
#include "AttackComponent.generated.h"

//==========================================================================
// DELEGATES
//==========================================================================
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackHit, AActor*, HitActor);

//==========================================================================
// CLASS: UAttackComponent
//==========================================================================
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ALPHA_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//==========================================================================
	// CONSTRUCTOR & PUBLIC FUNCTIONS
	//==========================================================================
	UAttackComponent();

	// Attack input handling
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void OnAttackInput();

	// Combo control
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void StopCombo();

	// Trace execution
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void PerformSwordTrace();

	// Animation notify handlers
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void HandleNotify_Hit();
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void HandleNotify_ComboWindowOpen();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void HandleNotify_ComboWindowClose();

	//==========================================================================
	// PUBLIC PROPERTIES
	//==========================================================================
	
	// Attack hit event delegate
	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnAttackHit OnAttackHit;

	// Combo state
	bool bComboWindowOpen = true;

protected:
	//==========================================================================
	// PROTECTED FUNCTIONS
	//==========================================================================
	virtual void BeginPlay() override;

	// Animation
	void PlayAttackMontage() const;
	void ResetCombo();
	void QueueNextAttack();

	// Trace system
	void DoSwordTrace();
	void SwordTraceTick();
	
	UFUNCTION()
	void MontageNotify_PerformTrace();

	UFUNCTION(BlueprintCallable, Category = "Combat|Trace")
	void HandleNotify_SwordTraceStart();

	UFUNCTION(BlueprintCallable, Category = "Combat|Trace")
	void HandleNotify_SwordTraceEnd();

	//==========================================================================
	// PROTECTED PROPERTIES
	//==========================================================================
	
	// Combo system
	UPROPERTY(EditAnywhere, Category = "Combat|Combo")
	int32 MaxCombo = 3;

	UPROPERTY(VisibleAnywhere, Category = "Combat|Combo")
	int32 CurrentComboIndex = 0;

	UPROPERTY(VisibleAnywhere, Category = "Combat|Combo")
	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, Category = "Combat|Combo")
	float ComboInputWindow = 0.4f;

	FTimerHandle ComboResetTimerHandle;
	bool bQueuedNextAttack = false;

	// Animation
	UPROPERTY(EditAnywhere, Category = "Combat|Animation")
	UAnimMontage* AttackMontage;

	// Trace parameters
	UPROPERTY(EditAnywhere, Category = "Combat|Trace")
	float TraceRadius = 15.f;

	UPROPERTY(EditAnywhere, Category = "Combat|Trace")
	FName TraceStartSocket = "SwordSocket_Start";

	UPROPERTY(EditAnywhere, Category = "Combat|Trace")
	FName TraceEndSocket = "SwordSocket_End";

	// Damage system
	UPROPERTY(EditAnywhere, Category = "Combat|Damage")
	float AttackDamage = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Combat|Damage")
	TSubclassOf<UDamageType> DamageTypeClass;

	// Visual/Audio effects
	UPROPERTY(EditAnywhere, Category = "Combat|FX")
	USoundBase* SwingSound;

	UPROPERTY(EditAnywhere, Category = "Combat|FX")
	UParticleSystem* HitParticle;
	
	// Hit tracking
	UPROPERTY()
	TSet<AActor*> AlreadyHitActors;

	// Continuous trace system
	UPROPERTY(EditAnywhere, Category = "Combat|Trace")
	bool bUseContinuousTrace = true;

	UPROPERTY(EditAnywhere, Category = "Combat|Trace", meta=(EditCondition="bUseContinuousTrace", ClampMin="0.005", ClampMax="0.05"))
	float TraceTickInterval = 0.015f;

	FTimerHandle SwordTraceTimerHandle;
};