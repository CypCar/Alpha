#include "World/Pickup.h"
#include "Components/InventoryComponent.h"
#include "Items/ItemBase.h"
#include "AlphaCharacter.h"

//==========================================================================
// CONSTRUCTOR
//==========================================================================
APickup::APickup()
{
    PrimaryActorTick.bCanEverTick = false;

    PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
    PickupMesh->SetSimulatePhysics(true);
    SetRootComponent(PickupMesh);

    PickupMesh->SetCollisionObjectType(ECC_GameTraceChannel1);
}

//==========================================================================
// GAME FLOW
//==========================================================================
void APickup::BeginPlay()
{
    Super::BeginPlay();
    InitializePickup(ItemQuantity);
}

//==========================================================================
// INITIALIZATION
//==========================================================================
void APickup::InitializePickup(const int32 InQuantity)
{
    if (!ItemRowHandle.IsNull())
    {
        const FItemData* ItemData = ItemRowHandle.GetRow<FItemData>(ItemRowHandle.RowName.ToString());

        ItemReference = NewObject<UItemBase>(this, UItemBase::StaticClass());

        // Initialize Item Properties
        ItemReference->ID = ItemData->ID;
        ItemReference->ItemType = ItemData->ItemType;
        ItemReference->ItemQuality = ItemData->ItemQuality;
        ItemReference->NumericData = ItemData->NumericData;
        ItemReference->TextData = ItemData->TextData;
        ItemReference->AssetData = ItemData->AssetData;
        ItemReference->ItemStatistics = ItemData->ItemStatistics;

        // Stackability and Quantity
        ItemReference->NumericData.bIsStackable = ItemData->NumericData.MaxStackSize > 1;
        InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);

        // Visual Setup
        PickupMesh->SetStaticMesh(ItemData->AssetData.Mesh);
        UpdateInteractableData();
    }
}

void APickup::InitializeDrop(const TObjectPtr<UItemBase>& ItemToDrop)
{
    ItemReference = UItemBase::CreateItemCopy(ItemToDrop, this);
    PickupMesh->SetStaticMesh(ItemReference->AssetData.Mesh);
    UpdateInteractableData();
}

void APickup::UpdateInteractableData()
{
    InteractableData.InteractableType = EInteractableType::Pickup;
    InteractableData.Action = ItemReference->TextData.InteractionText;
    InteractableData.Name = ItemReference->TextData.Name;
    InteractableData.Quantity = ItemReference->Quantity;
}

//==========================================================================
// INTERACTION INTERFACE
//==========================================================================
void APickup::BeginFocus()
{
    if (PickupMesh)
    {
        PickupMesh->SetRenderCustomDepth(true);
    }
}

void APickup::EndFocus()
{
    if (PickupMesh)
    {
        PickupMesh->SetRenderCustomDepth(false);
    }
}

void APickup::Interact(AAlphaCharacter* PlayerCharacter)
{
    if (PlayerCharacter)
    {
        TakePickup(PlayerCharacter);
    }
}

//==========================================================================
// PICKUP LOGIC
//==========================================================================
void APickup::TakePickup(const AAlphaCharacter* Taker)
{
    if (!IsPendingKillPending())
    {
        if (ItemReference)
        {
            if (UInventoryComponent* PlayerInventory = Taker->GetInventory())
            {
                const FItemAddResult AddResult = PlayerInventory->HandleAddItem(ItemReference);

                // Store the data for notification before potentially destroying the pickup
                FInteractableData LootData = InteractableData;
                LootData.Quantity = AddResult.AmountAdded; // Show actual amount added

                switch (AddResult.OperationResult)
                {
                case EItemAddResult::IAR_NoItemAdded:
                    break;
                    
                case EItemAddResult::IAR_PartialAmountItemAdded:
                    UpdateInteractableData();
                    Taker->UpdateInteractionWidget();
                    
                    // Notify character about loot pickup
                    if (AAlphaCharacter* NonConstTaker = const_cast<AAlphaCharacter*>(Taker))
                    {
                        NonConstTaker->NotifyLootPickedUp(LootData);
                    }
                    break;
                    
                case EItemAddResult::IAR_AllItemsAdded:
                    // Notify character about loot pickup before destruction
                    if (AAlphaCharacter* NonConstTaker = const_cast<AAlphaCharacter*>(Taker))
                    {
                        NonConstTaker->NotifyLootPickedUp(LootData);
                    }
                    Destroy();
                    break;
                    
                default:
                    break;
                }

                UE_LOG(LogTemp, Warning, TEXT("%s"), *AddResult.ResultMessage.ToString());
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Player inventory component is null!"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Pickup internal item reference was somehow null!"));
        }
    }
}

//==========================================================================
// EDITOR SUPPORT
//==========================================================================
#if WITH_EDITOR
void APickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(FDataTableRowHandle, RowName))
    {
        if (!ItemRowHandle.IsNull())
        {
            const FItemData* ItemData = ItemRowHandle.GetRow<FItemData>(ItemRowHandle.RowName.ToString());
            PickupMesh->SetStaticMesh(ItemData->AssetData.Mesh);
        }
    }
}
#endif