// TestDummyCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestDummyCharacter.generated.h"

class UWidgetComponent;
class UStatsComponent;


UCLASS()
class ALPHA_API ATestDummyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//======================================================================================
	// PROPERTIES & VARIABLES
	//======================================================================================
	/** Statystyki (HP/Stamina) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStatsComponent* StatsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess="true"))
	UWidgetComponent* StatsWidgetComponent;

	// --- ustawienia wygaszania widgetu ---
	UPROPERTY(EditAnywhere, Category="UI|Visibility")
	float WidgetFadeStartDistance = 1200.0f;

	UPROPERTY(EditAnywhere, Category="UI|Visibility")
	float WidgetFadeEndDistance = 1500.0f;

	UPROPERTY(EditAnywhere, Category="UI|Visibility")
	float WidgetFadeSpeed = 5.0f; // szybkość blendowania
	
	//======================================================================================
	// FUNCTIONS
	//======================================================================================
	ATestDummyCharacter();

	// Przechwycenie dmg z ApplyDamage / ApplyPointDamage
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,AActor* DamageCause) override;

	/** Reakcja na zmianę HP – tylko debug/log */
	UFUNCTION()
	void OnHealthChanged(float NewHealth, float Delta);
                                                
	/** Reakcja na śmierć */
	UFUNCTION()
	void OnDeath(AActor* DeadActor);
	
protected:
	//======================================================================================
	// PROPERTIES & VARIABLES
	//======================================================================================
	//======================================================================================
	// FUNCTIONS
	//======================================================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	

	




	
	

};
