
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameFramework/SaveGame.h"

#include "SaveSubsystem.generated.h"


UINTERFACE(BlueprintType)
class ALPHA_API USaveableInterface : public UInterface
{
	GENERATED_BODY()
};

class ALPHA_API ISaveableInterface
{
	GENERATED_BODY()
public:
	virtual void DoPreSave() {};
	virtual void DoPostLoad() {};
};


USTRUCT()
struct FSaveActorData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FName ActorName;

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	UClass* Class;

	UPROPERTY()
	TArray<uint8> ByteData;
};


USTRUCT()
struct FSubsystemData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<uint8> ByteData;
};


UCLASS()
class ALPHA_API USaveGameData : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString LevelName;

	UPROPERTY()
	TArray<FSubsystemData> SubsystemsData;

	UPROPERTY()
	TArray<FSaveActorData> ActorsData;
};


DECLARE_EVENT(USaveSubsystem, FGameLoaded);


UCLASS()
class ALPHA_API USaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	bool DeleteGame(FString SlotName);

	UFUNCTION(BlueprintCallable)
	bool SaveGame(FString SlotName);

	UFUNCTION(BlueprintCallable)
	bool LoadGame(FString SlotName);

	UFUNCTION(BlueprintCallable)
	TArray<FString> GetAllSaveGameSlotNames();

	FGameLoaded GameLoadedEvent;

private:
	UPROPERTY()
	USaveGameData* CurrSaveGameData = nullptr;

	void OnLevelLoaded(UWorld* World);
};
