// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "UserInterface/MainMenu.h"

#ifdef ALPHA_MainMenu_generated_h
#error "MainMenu.generated.h already included, missing '#pragma once' in MainMenu.h"
#endif
#define ALPHA_MainMenu_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UMainMenu ****************************************************************
ALPHA_API UClass* Z_Construct_UClass_UMainMenu_NoRegister();

#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_MainMenu_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMainMenu(); \
	friend struct Z_Construct_UClass_UMainMenu_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ALPHA_API UClass* Z_Construct_UClass_UMainMenu_NoRegister(); \
public: \
	DECLARE_CLASS2(UMainMenu, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Alpha"), Z_Construct_UClass_UMainMenu_NoRegister) \
	DECLARE_SERIALIZER(UMainMenu)


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_MainMenu_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMainMenu(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UMainMenu(UMainMenu&&) = delete; \
	UMainMenu(const UMainMenu&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMainMenu); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMainMenu); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMainMenu) \
	NO_API virtual ~UMainMenu();


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_MainMenu_h_13_PROLOG
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_MainMenu_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_MainMenu_h_16_INCLASS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_MainMenu_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UMainMenu;

// ********** End Class UMainMenu ******************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_MainMenu_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
