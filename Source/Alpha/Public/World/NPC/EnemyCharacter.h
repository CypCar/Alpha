#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UStatsComponent;
class UWidgetComponent;
class UBehaviorTree;
class AEnemyAIController;

//==========================================================================
// CLASS: AEnemyCharacter
//==========================================================================
UCLASS()
class ALPHA_API AEnemyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    //==========================================================================
    // CONSTRUCTOR & PUBLIC FUNCTIONS
    //==========================================================================
    AEnemyCharacter();

    // Damage System
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                           class AController* EventInstigator, AActor* DamageCauser) override;

    // Stats Accessors
    UFUNCTION(BlueprintPure, Category = "Stats")
    bool IsDead() const { return bIsDead; }

    UFUNCTION(BlueprintPure, Category = "Stats")
    float GetHealthPercent() const;

    // Stats Event Handlers
    UFUNCTION()
    void OnHealthChanged(float NewHealth, float Delta);

    UFUNCTION()
    void OnDeath(AActor* DeadActor);

    //==========================================================================
    // PUBLIC PROPERTIES
    //==========================================================================
    
    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStatsComponent* StatsComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    UWidgetComponent* StatsWidgetComponent;

    // AI System
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    bool bIsDead = false;

    // UI Visibility Settings
    UPROPERTY(EditAnywhere, Category = "UI|Visibility")
    float WidgetFadeStartDistance = 1200.0f;

    UPROPERTY(EditAnywhere, Category = "UI|Visibility")
    float WidgetFadeEndDistance = 1500.0f;

    UPROPERTY(EditAnywhere, Category = "UI|Visibility")
    float WidgetFadeSpeed = 5.0f;

protected:
    //==========================================================================
    // PROTECTED FUNCTIONS
    //==========================================================================
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
};