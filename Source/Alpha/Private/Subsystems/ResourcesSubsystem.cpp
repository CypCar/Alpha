// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/ResourcesSubsystem.h"
#include "Engine/Engine.h" 

bool UResourcesSubsystem::ConsumeResource(FGameplayTag Res, int32 Quantity) 
{

	if (Resources.Contains(Res) && Resources[Res] >= Quantity) 
	{
		Resources[Res] -= Quantity;
		OnResourceChange.Broadcast(Res, Resources[Res]);
		return true;
	}
	return false;
}

void UResourcesSubsystem::AddResource(FGameplayTag Res, int32 Quantity) 
{
	Resources.FindOrAdd(Res) += Quantity;

	OnResourceChange.Broadcast(Res, Resources[Res]);

	/*if (GEngine)// Debug info
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green,
			FString::Printf(TEXT("%s: %d points"), *Res.ToString(), Resources[Res]));
	}*/
}

int32 UResourcesSubsystem::GetResource(FGameplayTag Res) 
{
	if (Resources.Contains(Res)) 
	{
		return Resources[Res];
	}
	return 0;
}

void UResourcesSubsystem::ResetState() 
{
	Resources.Empty();
}
