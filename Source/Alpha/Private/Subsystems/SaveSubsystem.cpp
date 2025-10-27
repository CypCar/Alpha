
#include "Subsystems/SaveSubsystem.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/MemoryWriter.h"
#include "Subsystems/SubsystemCollection.h"
#include "Kismet/GameplayStatics.h"

bool USaveSubsystem::DeleteGame(FString SlotName)
{
	return UGameplayStatics::DeleteGameInSlot(SlotName, 0);
}

bool USaveSubsystem::SaveGame(FString SlotName)
{
	CurrSaveGameData = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));

	check(!SlotName.IsEmpty());

	CurrSaveGameData->LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);

	CurrSaveGameData->SubsystemsData.Empty();

	GetWorld()->ForEachSubsystem<UWorldSubsystem>([&](UWorldSubsystem* Subsystem)
		{
			if (ISaveableInterface* Saveable = Cast<ISaveableInterface>(Subsystem))
			{
				Saveable->DoPreSave();

				FMemoryWriter MemWriter(CurrSaveGameData->SubsystemsData.AddDefaulted_GetRef().ByteData);
				FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
				Ar.ArIsSaveGame = true;
				Ar.ArNoDelta = true;

				Subsystem->Serialize(Ar);
			}
		});

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveableInterface::StaticClass(), FoundActors);

	for (AActor* ActorToSave : FoundActors)
	{
		ISaveableInterface* Saveable = Cast<ISaveableInterface>(ActorToSave);
		if (Saveable)
		{
			Saveable->DoPreSave();
		}

		FSaveActorData ActorData;
		ActorData.ActorName = ActorToSave->GetFName();
		ActorData.Transform = ActorToSave->GetActorTransform();
		ActorData.Class = ActorToSave->GetClass();

		FMemoryWriter MemWriter(ActorData.ByteData);
		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
		Ar.ArIsSaveGame = true;
		Ar.ArNoDelta = true;
		ActorToSave->Serialize(Ar);

		for (UActorComponent* ComponentToSave : ActorToSave->GetComponents())
		{
			if (ISaveableInterface* SaveableComponent = Cast<ISaveableInterface>(ComponentToSave))
			{
				SaveableComponent->DoPreSave();
				ComponentToSave->Serialize(Ar);
			}
		}

		CurrSaveGameData->ActorsData.Add(ActorData);
	}

	return UGameplayStatics::SaveGameToSlot(CurrSaveGameData, SlotName, 0);
}

bool USaveSubsystem::LoadGame(FString SlotName)
{
	if (!UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		return false;
	}

	CurrSaveGameData = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	if (CurrSaveGameData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load save game"));
		return false;
	}
	
	UGameplayStatics::OpenLevel(GetWorld(), *CurrSaveGameData->LevelName);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &USaveSubsystem::OnLevelLoaded);

	return true;
}

void USaveSubsystem::OnLevelLoaded(UWorld* World)
{
	FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);

	if (CurrSaveGameData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load SvaeGame"));
		return;
	}

	//Subsystems
	int32 SSId = 0;
	TArray<ISaveableInterface*> SaveablesLoaded;

	GetWorld()->ForEachSubsystem<UWorldSubsystem>([&](UWorldSubsystem* Subsystem)
		{
			if (ISaveableInterface* Saveable = Cast<ISaveableInterface>(Subsystem))
			{
				FMemoryReader MemReader(CurrSaveGameData->SubsystemsData[SSId++].ByteData);
				FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
				Ar.ArIsSaveGame = true;
				Ar.ArNoDelta = true;
				Subsystem->Serialize(Ar);
				SaveablesLoaded.Add(Saveable);
			}
		});

	//Actors
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveableInterface::StaticClass(), FoundActors);

	for (FSaveActorData ActorData : CurrSaveGameData->ActorsData)
	{
		AActor* MatchingActor = nullptr;

		for (AActor* ActorInGame : FoundActors)
		{
			if (ActorData.ActorName == ActorInGame->GetFName())
			{
				MatchingActor = ActorInGame;
				break;
			}
		}

		if (!MatchingActor)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Name = ActorData.ActorName;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			MatchingActor = GetWorld()->SpawnActor<AActor>(ActorData.Class, ActorData.Transform, SpawnParams);
			FoundActors.Add(MatchingActor);
		}

		check(MatchingActor);

		MatchingActor->SetActorTransform(ActorData.Transform);
	}

	for (FSaveActorData ActorData : CurrSaveGameData->ActorsData)
	{
		AActor* MatchingActor = nullptr;

		for (AActor* ActorInGame : FoundActors)
		{
			if (ActorData.ActorName == ActorInGame->GetFName())
			{
				MatchingActor = ActorInGame;
				break;
			}
		}
		check(MatchingActor);

		FMemoryReader MemReader(ActorData.ByteData);
		FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
		Ar.ArIsSaveGame = true;
		Ar.ArNoDelta = true;
		MatchingActor->Serialize(Ar);

		if ( ISaveableInterface* Saveable = Cast<ISaveableInterface>(MatchingActor))
		{
			SaveablesLoaded.Add(Saveable);
		}

		//Components
		for (UActorComponent* ComponentToSave : MatchingActor->GetComponents())
		{
			if (ISaveableInterface* SaveableComponent = Cast<ISaveableInterface>(ComponentToSave))
			{
				ComponentToSave->Serialize(Ar);
				SaveablesLoaded.Add(SaveableComponent);

			}
		}
	}

	//Deleting Actors that are no longer there
	for (AActor* PresentSaveableActor : FoundActors)
	{
		ISaveableInterface* Saveable = Cast<ISaveableInterface>(PresentSaveableActor);

		if (Saveable && !SaveablesLoaded.Contains(Saveable))
		{
			PresentSaveableActor->Destroy();
		}
	}

	for (ISaveableInterface* Saveable : SaveablesLoaded)
	{
		Saveable->DoPostLoad();
	}

	//Make sure all input related stuff is reset in case of popup visible during save
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	GetWorld()->GetFirstPlayerController()->SetInputMode(InputMode);
	GetWorld()->GetFirstPlayerController()->FlushPressedKeys();

	GameLoadedEvent.Broadcast();

}

TArray<FString> USaveSubsystem::GetAllSaveGameSlotNames()
{
	class FFindSavesVisitor : public IPlatformFile::FDirectoryVisitor {
	public:
		FFindSavesVisitor() {}

		virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
		{
			if (!bIsDirectory)
			{
				FString FullFilePath (FilenameOrDirectory);
				if (FPaths::GetExtension( FullFilePath) == TEXT("sav"))
				{
					IPlatformFile& File = FPlatformFileManager::Get().GetPlatformFile();
					FString CleanFilename = FPaths::GetBaseFilename(FullFilePath);
					CleanFilename = CleanFilename.Replace(TEXT(".sav"), TEXT(""));
					SavesFound.Add(File.GetTimeStamp(*FullFilePath).ToUnixTimestamp(), CleanFilename);
				}
			}
			return true;
		}
		TMultiMap<int64, FString> SavesFound;
	};

	TArray<FString> Saves;
	const FString SavesFolder = FPaths::ProjectSavedDir() + TEXT("SaveGames");

	if (!SavesFolder.IsEmpty())
	{
		FFindSavesVisitor Visitor;
		FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*SavesFolder, Visitor);
		Visitor.SavesFound.KeySort([](const int64& InA, const int64& InB)
			{
				return InA > InB;
			});
		Visitor.SavesFound.GenerateValueArray(Saves);
	}

	return Saves;
}