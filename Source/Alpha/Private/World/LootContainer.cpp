// LootContainer.cpp

#include "World/LootContainer.h"
#include "UserInterface/AlphaHUD.h"
#include "Items/ItemBase.h"
#include "Components/InventoryComponent.h"

// == ctor ==

ALootContainer::ALootContainer()
{ PrimaryActorTick.bCanEverTick = false;
	ContainerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ContainerMesh"));
	SetRootComponent(ContainerMesh);
	ContainerMesh->SetSimulatePhysics(false);

	ContainerDisplayName = NSLOCTEXT("LootContainer", "DefaultName", "Container");
}

void ALootContainer::BeginPlay()
{
	Super::BeginPlay(); InitializePickup(ItemQuantity);
	
}

void ALootContainer::BeginFocus()
{
	if (ContainerMesh)
	{
		if (IsEmpty()) return;
		ContainerMesh->SetRenderCustomDepth(true);
	}
}

void ALootContainer::EndFocus()
{
	if (ContainerMesh)
	{
		ContainerMesh->SetRenderCustomDepth(false);
	}
}

bool ALootContainer::IsEmpty() const
{
	if (ItemReference->Quantity > 0) return false;
	return true;
}

void ALootContainer::InitializePickup(const int32 InQuantity)
{
	if (!ItemRowHandle.IsNull())
	{
		const FItemData* ItemData = ItemRowHandle.GetRow<FItemData>(ItemRowHandle.RowName.ToString());

		ItemReference = NewObject<UItemBase>(this, UItemBase::StaticClass());
		
		ItemReference->ID = ItemData->ID;
		ItemReference->ItemType = ItemData->ItemType;
		ItemReference->ItemQuality = ItemData->ItemQuality;
		ItemReference->NumericData = ItemData->NumericData;
		ItemReference->TextData = ItemData->TextData;
		ItemReference->AssetData = ItemData->AssetData;
		
		ItemReference->NumericData.bIsStackable = ItemData->NumericData.MaxStackSize > 1;
		InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);
		UpdateInteractableData();
	}
}

void ALootContainer::Interact(AAlphaCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		TakeItems(PlayerCharacter);
	}
}

void ALootContainer::UpdateInteractableData()
{
	InstanceInteractableData.InteractableType = EInteractableType::Container;
	InstanceInteractableData.Action = ItemReference->TextData.InteractionText;
	InstanceInteractableData.Name = ContainerDisplayName;
	InstanceInteractableData.Quantity = ItemReference->Quantity;
	InteractableData = InstanceInteractableData;
}

void ALootContainer::TakeItems(AAlphaCharacter* Taker)
{
    if (IsPendingKillPending() || !ItemReference) return;

    if (UInventoryComponent* PlayerInventory = Taker->GetInventory())
    {
        // 1) stan PRZED
        const int32 PreviousQuantity = ItemReference->Quantity;

        // 2) dodaj do ekwipunku
        const FItemAddResult AddResult = PlayerInventory->HandleAddItem(ItemReference);

        // 3) policz AddedNow z uwzględnieniem wyniku operacji
        int32 AddedNow = 0;

        switch (AddResult.OperationResult)
        {
        case EItemAddResult::IAR_NoItemAdded:
            AddedNow = 0;
            break;

        case EItemAddResult::IAR_PartialAmountItemAdded:
        {
            // Jeżeli HandleAddItem zmniejsza ilość w kontenerze, delta zadziała:
            const int32 AfterQty = ItemReference ? ItemReference->Quantity : PreviousQuantity;
            AddedNow = FMath::Max(PreviousQuantity - AfterQty, 0);

            // Aktualizuj widget interakcji (zostało coś w skrzyni)
            UpdateInteractableData();
            Taker->UpdateInteractionWidget();
            break;
        }

        case EItemAddResult::IAR_AllItemsAdded:
        {
            // Całość poszła do gracza → AddedNow = to, co było
            AddedNow = PreviousQuantity;

            // (opcjonalnie) „wyzeruj” stan kontenera, żeby logika była spójna
            if (ItemReference) { ItemReference->SetQuantity(0); }
            UpdateInteractableData();

            MakeNonInteractableButBlocking();
            break;
        }
        }

        // 4) Pokaż HUD tylko jeśli coś realnie dodano
        if (AddedNow > 0)
        {
            FInteractableData TempData;
            TempData.Name     = ItemReference->TextData.Name;
            TempData.Quantity = AddedNow;

            if (Taker && Taker->IsLocallyControlled())
            {
                if (APlayerController* PC = Cast<APlayerController>(Taker->GetController()))
                {
                    if (AAlphaHUD* HUD = PC->GetHUD<AAlphaHUD>())
                    {
                        HUD->EnqueueLoot(TempData);
                    }
                }
            }

            // szybki debug na ekran, żeby zobaczyć 4 kontenery z rzędu
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green,
                    FString::Printf(TEXT("Loot: %s x%d"), *TempData.Name.ToString(), TempData.Quantity));
            }
        }

        UE_LOG(LogTemp, Warning, TEXT("%s"), *AddResult.ResultMessage.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player inventory component is null!"));
    }
}


void ALootContainer::MakeNonInteractableButBlocking()
{
	if (!ContainerMesh) return;
	ContainerMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ContainerMesh->SetCollisionObjectType(ECC_WorldStatic);
	ContainerMesh->SetCollisionResponseToAllChannels(ECR_Block);
	// Ignore interaction trace channel (adjust if you use custom channel)
	ContainerMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	ContainerMesh->SetGenerateOverlapEvents(false);
}

#if WITH_EDITOR
void ALootContainer::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(FDataTableRowHandle, RowName))
	{
		if (!ItemRowHandle.IsNull()) { const FItemData* ItemData = ItemRowHandle.GetRow<FItemData>(ItemRowHandle.RowName.ToString()); }
	}
}
#endif