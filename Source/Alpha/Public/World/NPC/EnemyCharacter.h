#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UStatsComponent;
class UWidgetComponent;
class UBehaviorTree;
class AEnemyAIController; // forward

UCLASS()
class ALPHA_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	/** Przyjmowanie obrażeń z ApplyDamage / ApplyPointDamage */
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	UPROPERTY(EditAnywhere, Category="UI|Visibility")
	float WidgetFadeStartDistance = 1200.0f;

	UPROPERTY(EditAnywhere, Category="UI|Visibility")
	float WidgetFadeEndDistance = 1500.0f;

	UPROPERTY(EditAnywhere, Category="UI|Visibility")
	float WidgetFadeSpeed = 5.0f;
	
	/** Statystyki (HP/Stamina) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStatsComponent* StatsComponent;

	/** Pasek HP/Staminy nad głową (opcjonalnie) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	UWidgetComponent* StatsWidgetComponent;

	/** BehaviorTree tego wroga (ustawisz w BP) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI")
	UBehaviorTree* BehaviorTreeAsset;

	/** Czy wróg jest martwy (dla BT / animacji) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	bool bIsDead = false;

	// --- Delegaty z StatsComponent ---

	UFUNCTION()
	void OnHealthChanged(float NewHealth, float Delta);

	UFUNCTION()
	void OnDeath(AActor* DeadActor);

	// Przydatne dla BT / animacji
	UFUNCTION(BlueprintPure, Category="Stats")
	bool IsDead() const { return bIsDead; }

	UFUNCTION(BlueprintPure, Category="Stats")
	float GetHealthPercent() const;
};
