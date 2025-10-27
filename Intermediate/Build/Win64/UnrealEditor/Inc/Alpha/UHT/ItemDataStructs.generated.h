// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Data/ItemDataStructs.h"

#ifdef ALPHA_ItemDataStructs_generated_h
#error "ItemDataStructs.generated.h already included, missing '#pragma once' in ItemDataStructs.h"
#endif
#define ALPHA_ItemDataStructs_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FItemStatistics ***************************************************
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Data_ItemDataStructs_h_32_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FItemStatistics_Statics; \
	ALPHA_API static class UScriptStruct* StaticStruct();


struct FItemStatistics;
// ********** End ScriptStruct FItemStatistics *****************************************************

// ********** Begin ScriptStruct FItemTextData *****************************************************
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Data_ItemDataStructs_h_51_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FItemTextData_Statics; \
	ALPHA_API static class UScriptStruct* StaticStruct();


struct FItemTextData;
// ********** End ScriptStruct FItemTextData *******************************************************

// ********** Begin ScriptStruct FItemNumericData **************************************************
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Data_ItemDataStructs_h_69_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FItemNumericData_Statics; \
	ALPHA_API static class UScriptStruct* StaticStruct();


struct FItemNumericData;
// ********** End ScriptStruct FItemNumericData ****************************************************

// ********** Begin ScriptStruct FItemAssetData ****************************************************
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Data_ItemDataStructs_h_84_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FItemAssetData_Statics; \
	ALPHA_API static class UScriptStruct* StaticStruct();


struct FItemAssetData;
// ********** End ScriptStruct FItemAssetData ******************************************************

// ********** Begin ScriptStruct FItemData *********************************************************
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Data_ItemDataStructs_h_96_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FItemData_Statics; \
	ALPHA_API static class UScriptStruct* StaticStruct(); \
	typedef FTableRowBase Super;


struct FItemData;
// ********** End ScriptStruct FItemData ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Data_ItemDataStructs_h

// ********** Begin Enum EItemQuality **************************************************************
#define FOREACH_ENUM_EITEMQUALITY(op) \
	op(EItemQuality::Shoddy) \
	op(EItemQuality::Common) \
	op(EItemQuality::Qulaity) \
	op(EItemQuality::Masterwork) \
	op(EItemQuality::Grandmaster) 

enum class EItemQuality : uint8;
template<> struct TIsUEnumClass<EItemQuality> { enum { Value = true }; };
template<> ALPHA_API UEnum* StaticEnum<EItemQuality>();
// ********** End Enum EItemQuality ****************************************************************

// ********** Begin Enum EItemType *****************************************************************
#define FOREACH_ENUM_EITEMTYPE(op) \
	op(EItemType::Armor) \
	op(EItemType::Weapon) \
	op(EItemType::Shield) \
	op(EItemType::Spell) \
	op(EItemType::Consumable) \
	op(EItemType::Quest) \
	op(EItemType::Mundane) 

enum class EItemType : uint8;
template<> struct TIsUEnumClass<EItemType> { enum { Value = true }; };
template<> ALPHA_API UEnum* StaticEnum<EItemType>();
// ********** End Enum EItemType *******************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
