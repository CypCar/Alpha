// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "UserInterface/Interaction/LootRowWidget.h"

#ifdef ALPHA_LootRowWidget_generated_h
#error "LootRowWidget.generated.h already included, missing '#pragma once' in LootRowWidget.h"
#endif
#define ALPHA_LootRowWidget_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ULootRowWidget ***********************************************************
ALPHA_API UClass* Z_Construct_UClass_ULootRowWidget_NoRegister();

#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootRowWidget_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULootRowWidget(); \
	friend struct Z_Construct_UClass_ULootRowWidget_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ALPHA_API UClass* Z_Construct_UClass_ULootRowWidget_NoRegister(); \
public: \
	DECLARE_CLASS2(ULootRowWidget, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Alpha"), Z_Construct_UClass_ULootRowWidget_NoRegister) \
	DECLARE_SERIALIZER(ULootRowWidget)


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootRowWidget_h_12_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootRowWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	ULootRowWidget(ULootRowWidget&&) = delete; \
	ULootRowWidget(const ULootRowWidget&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootRowWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootRowWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootRowWidget) \
	NO_API virtual ~ULootRowWidget();


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootRowWidget_h_9_PROLOG
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootRowWidget_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootRowWidget_h_12_INCLASS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootRowWidget_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ULootRowWidget;

// ********** End Class ULootRowWidget *************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootRowWidget_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
