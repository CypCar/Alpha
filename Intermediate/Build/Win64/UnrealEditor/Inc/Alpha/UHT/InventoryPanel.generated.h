// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "UserInterface/Inventory/InventoryPanel.h"

#ifdef ALPHA_InventoryPanel_generated_h
#error "InventoryPanel.generated.h already included, missing '#pragma once' in InventoryPanel.h"
#endif
#define ALPHA_InventoryPanel_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UInventoryPanel **********************************************************
ALPHA_API UClass* Z_Construct_UClass_UInventoryPanel_NoRegister();

#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryPanel_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUInventoryPanel(); \
	friend struct Z_Construct_UClass_UInventoryPanel_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ALPHA_API UClass* Z_Construct_UClass_UInventoryPanel_NoRegister(); \
public: \
	DECLARE_CLASS2(UInventoryPanel, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Alpha"), Z_Construct_UClass_UInventoryPanel_NoRegister) \
	DECLARE_SERIALIZER(UInventoryPanel)


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryPanel_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UInventoryPanel(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UInventoryPanel(UInventoryPanel&&) = delete; \
	UInventoryPanel(const UInventoryPanel&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInventoryPanel); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInventoryPanel); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInventoryPanel) \
	NO_API virtual ~UInventoryPanel();


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryPanel_h_12_PROLOG
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryPanel_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryPanel_h_15_INCLASS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryPanel_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UInventoryPanel;

// ********** End Class UInventoryPanel ************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryPanel_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
