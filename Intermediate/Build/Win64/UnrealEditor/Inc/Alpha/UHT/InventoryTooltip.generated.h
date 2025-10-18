// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "UserInterface/Inventory/InventoryTooltip.h"

#ifdef ALPHA_InventoryTooltip_generated_h
#error "InventoryTooltip.generated.h already included, missing '#pragma once' in InventoryTooltip.h"
#endif
#define ALPHA_InventoryTooltip_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UInventoryTooltip ********************************************************
ALPHA_API UClass* Z_Construct_UClass_UInventoryTooltip_NoRegister();

#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryTooltip_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUInventoryTooltip(); \
	friend struct Z_Construct_UClass_UInventoryTooltip_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ALPHA_API UClass* Z_Construct_UClass_UInventoryTooltip_NoRegister(); \
public: \
	DECLARE_CLASS2(UInventoryTooltip, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Alpha"), Z_Construct_UClass_UInventoryTooltip_NoRegister) \
	DECLARE_SERIALIZER(UInventoryTooltip)


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryTooltip_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UInventoryTooltip(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UInventoryTooltip(UInventoryTooltip&&) = delete; \
	UInventoryTooltip(const UInventoryTooltip&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInventoryTooltip); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInventoryTooltip); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInventoryTooltip) \
	NO_API virtual ~UInventoryTooltip();


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryTooltip_h_12_PROLOG
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryTooltip_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryTooltip_h_15_INCLASS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryTooltip_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UInventoryTooltip;

// ********** End Class UInventoryTooltip **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryTooltip_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
