// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Components/InventoryComponent.h"

#ifdef ALPHA_InventoryComponent_generated_h
#error "InventoryComponent.generated.h already included, missing '#pragma once' in InventoryComponent.h"
#endif
#define ALPHA_InventoryComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class UItemBase;
struct FItemAddResult;

// ********** Begin ScriptStruct FItemAddResult ****************************************************
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Components_InventoryComponent_h_24_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FItemAddResult_Statics; \
	ALPHA_API static class UScriptStruct* StaticStruct();


struct FItemAddResult;
// ********** End ScriptStruct FItemAddResult ******************************************************

// ********** Begin Class UInventoryComponent ******************************************************
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Components_InventoryComponent_h_72_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSetWeightCapacity); \
	DECLARE_FUNCTION(execSetSlotsCapacity); \
	DECLARE_FUNCTION(execGetInventoryContents); \
	DECLARE_FUNCTION(execGetSlotsCapacity); \
	DECLARE_FUNCTION(execGetWeightCapacity); \
	DECLARE_FUNCTION(execGetInventoryTotalWeight); \
	DECLARE_FUNCTION(execSplitExistingStack); \
	DECLARE_FUNCTION(execRemoveAmountOfItem); \
	DECLARE_FUNCTION(execRemoveSingleInstanceOfItem); \
	DECLARE_FUNCTION(execFindNextPartialStack); \
	DECLARE_FUNCTION(execFindNextItemByID); \
	DECLARE_FUNCTION(execFindMatchingItem); \
	DECLARE_FUNCTION(execHandleAddItem);


ALPHA_API UClass* Z_Construct_UClass_UInventoryComponent_NoRegister();

#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Components_InventoryComponent_h_72_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUInventoryComponent(); \
	friend struct Z_Construct_UClass_UInventoryComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ALPHA_API UClass* Z_Construct_UClass_UInventoryComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UInventoryComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Alpha"), Z_Construct_UClass_UInventoryComponent_NoRegister) \
	DECLARE_SERIALIZER(UInventoryComponent)


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Components_InventoryComponent_h_72_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UInventoryComponent(UInventoryComponent&&) = delete; \
	UInventoryComponent(const UInventoryComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInventoryComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInventoryComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UInventoryComponent) \
	NO_API virtual ~UInventoryComponent();


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Components_InventoryComponent_h_69_PROLOG
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Components_InventoryComponent_h_72_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Components_InventoryComponent_h_72_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Components_InventoryComponent_h_72_INCLASS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Components_InventoryComponent_h_72_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UInventoryComponent;

// ********** End Class UInventoryComponent ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Components_InventoryComponent_h

// ********** Begin Enum EItemAddResult ************************************************************
#define FOREACH_ENUM_EITEMADDRESULT(op) \
	op(EItemAddResult::IAR_NoItemAdded) \
	op(EItemAddResult::IAR_PartialAmountItemAdded) \
	op(EItemAddResult::IAR_AllItemsAdded) 

enum class EItemAddResult : uint8;
template<> struct TIsUEnumClass<EItemAddResult> { enum { Value = true }; };
template<> ALPHA_API UEnum* StaticEnum<EItemAddResult>();
// ********** End Enum EItemAddResult **************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
