// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Items/ItemBase.h"

#ifdef ALPHA_ItemBase_generated_h
#error "ItemBase.generated.h already included, missing '#pragma once' in ItemBase.h"
#endif
#define ALPHA_ItemBase_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class AAlphaCharacter;
class UItemBase;

// ********** Begin Class UItemBase ****************************************************************
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Items_ItemBase_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execUse); \
	DECLARE_FUNCTION(execSetQuantity); \
	DECLARE_FUNCTION(execIsFullItemStack); \
	DECLARE_FUNCTION(execGetItemSingleWeight); \
	DECLARE_FUNCTION(execGetItemStackWeight); \
	DECLARE_FUNCTION(execCreateItemCopy);


ALPHA_API UClass* Z_Construct_UClass_UItemBase_NoRegister();

#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Items_ItemBase_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUItemBase(); \
	friend struct Z_Construct_UClass_UItemBase_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ALPHA_API UClass* Z_Construct_UClass_UItemBase_NoRegister(); \
public: \
	DECLARE_CLASS2(UItemBase, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Alpha"), Z_Construct_UClass_UItemBase_NoRegister) \
	DECLARE_SERIALIZER(UItemBase)


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Items_ItemBase_h_16_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UItemBase(UItemBase&&) = delete; \
	UItemBase(const UItemBase&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UItemBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UItemBase); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UItemBase) \
	NO_API virtual ~UItemBase();


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Items_ItemBase_h_13_PROLOG
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Items_ItemBase_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Items_ItemBase_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Items_ItemBase_h_16_INCLASS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Items_ItemBase_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UItemBase;

// ********** End Class UItemBase ******************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Items_ItemBase_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
