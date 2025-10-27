// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "SaveSubsystem.h"
#include "ResourcesSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FResourceChangeEvent, FGameplayTag, Resource, int32, NewQuantity);

UCLASS()
class ALPHA_API UResourcesSubsystem : public UWorldSubsystem , public ISaveableInterface
{
	GENERATED_BODY()
	
public:
	//void DoPostLoad() override;

	UFUNCTION(BlueprintCallable)
	bool ConsumeResource(FGameplayTag Res, int32 Quantity);

	UFUNCTION(BlueprintCallable)
	void AddResource(FGameplayTag Res, int32 Quantity);

	UFUNCTION(BlueprintCallable)
	int32 GetResource(FGameplayTag Res);

	void ResetState();

	UPROPERTY(BlueprintAssignable)
	FResourceChangeEvent OnResourceChange;

private:
	UPROPERTY(SaveGame)
	TMap<FGameplayTag, int32> Resources;
};
