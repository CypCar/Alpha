#include "UserInterface/AlphaHUD.h"

#include "World/LootContainer.h"
#include "UserInterface/MainMenu.h"
#include "UserInterface/Interaction/InteractionWidget.h"
#include "UserInterface/Inventory/ContainerInterface.h"
#include "UserInterface/Interaction/LootWindowWidget.h"

AAlphaHUD::AAlphaHUD() :
	bMainMenuOpen(false),
	bContainerInterfaceOpen(false),
	bInteractionWidgetVisible(false)
{
}

void AAlphaHUD::BeginPlay()
{
	Super::BeginPlay();
	CreateGameWidgets();
}

bool AAlphaHUD::HasAnyMenuOpen() const
{
	return bMainMenuOpen || bContainerInterfaceOpen;
}

void AAlphaHUD::DisplayMenu()
{
	bMainMenuOpen = true;
	MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

void AAlphaHUD::HideMenu()
{
	bMainMenuOpen = false;
	MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AAlphaHUD::ToggleMenu()
{
	if (bMainMenuOpen)
	{
		HideMenu();
		const FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(false);
	}
	else
	{
		DisplayMenu();
		const FInputModeGameAndUI InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(true);
	}
}

void AAlphaHUD::ShowCrosshair() const
{
	CrosshairWidget->SetVisibility(ESlateVisibility::Visible);
}

void AAlphaHUD::HideCrosshair() const
{
	CrosshairWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AAlphaHUD::ShowInteractionWidget()
{
	bInteractionWidgetVisible = true;
	InteractionWidget->SetVisibility(ESlateVisibility::Visible);
}

void AAlphaHUD::HideInteractionWidget()
{
	bInteractionWidgetVisible = false;
	InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AAlphaHUD::UpdateInteractionWidget(const FInteractableData* InteractableData) const
{
	if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}

	InteractionWidget->UpdateWidget(InteractableData);
}

void AAlphaHUD::CreateGameWidgets()
{
    // MainMenuWidget
    if (IsValid(MainMenuClass))
    {
        MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
        MainMenuWidget->AddToViewport(5);
        MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s: MainMenuWidgetClass was null!"), ANSI_TO_TCHAR(__FUNCTION__));
    }

    // InteractionWidget
    if (IsValid(InteractionWidgetClass))
    {
        InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
        InteractionWidget->AddToViewport(0);
        InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s: InteractionWidgetClass was null!"), ANSI_TO_TCHAR(__FUNCTION__));
    }

    // CrosshairWidget
    if (IsValid(CrosshairWidgetClass))
    {
        CrosshairWidget = CreateWidget<UUserWidget>(GetWorld(), CrosshairWidgetClass);
        CrosshairWidget->AddToViewport(0);
        CrosshairWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s: CrosshairWidgetClass was null!"), ANSI_TO_TCHAR(__FUNCTION__));
    }

    // LootWindowWidget
    if (IsValid(LootWindowWidgetClass))
    {
        if (APlayerController* PlayerController = GetOwningPlayerController())
        {
            LootWindowWidget = CreateWidget<ULootWindowWidget>(PlayerController, LootWindowWidgetClass);
            LootWindowWidget->AddToViewport();
            LootWindowWidget->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s: LootWindowWidgetClass was null!"), ANSI_TO_TCHAR(__FUNCTION__));
    }

    // ContainerInterface - TERAZ OSOBNY WIDGET
    if (IsValid(ContainerInterfaceClass))
    {
        APlayerController* PC = GetOwningPlayerController();
        ContainerInterface = CreateWidget<UContainerInterface>(PC, ContainerInterfaceClass);
        
        if (ContainerInterface)
        {
            ContainerInterface->AddToViewport(10); // Wyższy Z-order
            ContainerInterface->SetVisibility(ESlateVisibility::Collapsed);
            ContainerInterface->CloseContainerInterface.BindUObject(this, &AAlphaHUD::HideContainerInterface);
            
            UE_LOG(LogTemp, Log, TEXT("CreateGameWidgets: Created separate ContainerInterface"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("CreateGameWidgets: Failed to create ContainerInterface!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("CreateGameWidgets: ContainerInterfaceClass is null!"));
    }
}

void AAlphaHUD::ShowContainerInterface(AContainer* TargetContainer)
{
	if (!ContainerInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShowContainerInterface: ContainerInterface is null!"));
		return;
	}

	// Podepnij do kontenera jeśli podano
	if (TargetContainer)
	{
		SetTargetContainer(TargetContainer);
	}

	// Pokaż widget
	bContainerInterfaceOpen = true;
	bContainerInterfaceManuallyOpened = true; // DODAJ FLAGĘ
	ContainerInterface->SetVisibility(ESlateVisibility::Visible);
    
	// Zmień tryb inputu
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	GetOwningPlayerController()->SetInputMode(InputMode);
	GetOwningPlayerController()->SetShowMouseCursor(true);
    
	// Ukryj interakcję jeśli jest widoczna
	HideInteractionWidget();
    
	UE_LOG(LogTemp, Log, TEXT("ShowContainerInterface: Container interface shown"));
}

void AAlphaHUD::HideContainerInterface(bool bSuccess)
{
	if (ContainerInterface)
	{
		bContainerInterfaceOpen = false;
		bContainerInterfaceManuallyOpened = false; // ZRESETUJ FLAGĘ
		ContainerInterface->SetVisibility(ESlateVisibility::Collapsed);
		ContainerInterface->ClearTargetContainer();
        
		// Przywróć tryb gry
		FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(false);
        
		UE_LOG(LogTemp, Log, TEXT("HideContainerInterface: Container interface hidden"));
	}
}

void AAlphaHUD::SetTargetContainer(AContainer* TargetContainer)
{
    if (!ContainerInterface)
    {
        UE_LOG(LogTemp, Warning, TEXT("SetTargetContainer: ContainerInterface is null!"));
        return;
    }

    // Podepnij do kontenera
    ContainerInterface->LinkContainerInterface(TargetContainer);
    UE_LOG(LogTemp, Log, TEXT("SetTargetContainer: Linked to container %s"), *TargetContainer->GetName());
}

void AAlphaHUD::ClearTargetContainer()
{
	HideContainerInterface();
	UE_LOG(LogTemp, Log, TEXT("ClearTargetContainer: Called"));
}

AContainer* AAlphaHUD::GetCurrentContainer() const
{
	if (ContainerInterface)
	{
		return ContainerInterface->GetTargetContainer();
	}
	return nullptr;
}
