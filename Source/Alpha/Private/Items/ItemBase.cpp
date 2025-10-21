// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"
//#include "Alpha/AlphaCharacter.h"
#include "Components/InventoryComponent.h"

UItemBase::UItemBase() : bIsCopy(false), bIsPickup(false)
{

}

void UItemBase::ResetItemFlags()
{
	bIsCopy = false;
	bIsPickup = false;
}

UItemBase* UItemBase::CreateItemCopy() const
{
	UItemBase* ItemCopy = NewObject<UItemBase>(StaticClass());

	ItemCopy->ID = this->ID;
	ItemCopy->ItemType = this->ItemType;
	ItemCopy->ItemQuality = this->ItemQuality;
	ItemCopy->ItemStatistics = this->ItemStatistics;
	ItemCopy->TextData = this->TextData;
	ItemCopy->NumericData = this->NumericData;
	ItemCopy->AssetData = this->AssetData;
	ItemCopy->Quantity = this->Quantity;

	ItemCopy->bIsCopy = true;

	return ItemCopy;
}

void UItemBase::SetQuantity(const int32 NewQuantity)
{
	if (NewQuantity != this->Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, this->NumericData.bIsStackable ? this->NumericData.MaxStackSize : 1);

		if (this->OwningInventory)
		{
			if (this->Quantity <= 0)
			{
				this->OwningInventory->RemoveSingleInstanceOfItem(this);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ItemBase OwningInventory was null (item may be a pickup)."));
		}
	}
}

void UItemBase::Use(AAlphaCharacter* Character)
{

}