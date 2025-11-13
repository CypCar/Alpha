// TestDummyCharacter.h
#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestDummyCharacter.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class UWidgetComponent;
class UStatsComponent;

//==========================================================================
// CLASS: ATestDummyCharacter
//==========================================================================
UCLASS()
class ALPHA_API ATestDummyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    //==========================================================================
    // CONSTRUCTOR & PUBLIC FUNCTIONS
    //==========================================================================
    ATestDummyCharacter();

    // Damage System
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, 
                           AController* EventInstigator, AActor* DamageCauser) override;

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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
    UWidgetComponent* StatsWidgetComponent;

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