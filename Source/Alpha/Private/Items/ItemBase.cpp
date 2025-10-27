// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"
#include "Alpha/AlphaCharacter.h"


UItemBase::UItemBase()
{

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

	return ItemCopy;
}

void UItemBase::SetQuantity(const int32 NewQuantity)
{
	if (NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, NumericData.bIsStackable ? NumericData.MaxStackSize : 1);

		/*if (OwningInventory)
		{
			if (Quantity <= 0)
			{
				OwningInventory->RemoveItem(this);
			}
		}*/
	}
}

void UItemBase::Use(AAlphaCharacter* Character)
{

}