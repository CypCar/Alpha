// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "UserInterface/Interaction/LootWindowWidget.h"

#ifdef ALPHA_LootWindowWidget_generated_h
#error "LootWindowWidget.generated.h already included, missing '#pragma once' in LootWindowWidget.h"
#endif
#define ALPHA_LootWindowWidget_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ULootWindowWidget ********************************************************
ALPHA_API UClass* Z_Construct_UClass_ULootWindowWidget_NoRegister();

#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootWindowWidget_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULootWindowWidget(); \
	friend struct Z_Construct_UClass_ULootWindowWidget_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ALPHA_API UClass* Z_Construct_UClass_ULootWindowWidget_NoRegister(); \
public: \
	DECLARE_CLASS2(ULootWindowWidget, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Alpha"), Z_Construct_UClass_ULootWindowWidget_NoRegister) \
	DECLARE_SERIALIZER(ULootWindowWidget)


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootWindowWidget_h_13_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootWindowWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	ULootWindowWidget(ULootWindowWidget&&) = delete; \
	ULootWindowWidget(const ULootWindowWidget&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootWindowWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootWindowWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootWindowWidget) \
	NO_API virtual ~ULootWindowWidget();


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootWindowWidget_h_10_PROLOG
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootWindowWidget_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootWindowWidget_h_13_INCLASS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootWindowWidget_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ULootWindowWidget;

// ********** End Class ULootWindowWidget **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootWindowWidget_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
