// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AlphaGameMode.h"

#ifdef ALPHA_AlphaGameMode_generated_h
#error "AlphaGameMode.generated.h already included, missing '#pragma once' in AlphaGameMode.h"
#endif
#define ALPHA_AlphaGameMode_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AAlphaGameMode ***********************************************************
ALPHA_API UClass* Z_Construct_UClass_AAlphaGameMode_NoRegister();

#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaGameMode_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAAlphaGameMode(); \
	friend struct Z_Construct_UClass_AAlphaGameMode_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ALPHA_API UClass* Z_Construct_UClass_AAlphaGameMode_NoRegister(); \
public: \
	DECLARE_CLASS2(AAlphaGameMode, AGameModeBase, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Alpha"), Z_Construct_UClass_AAlphaGameMode_NoRegister) \
	DECLARE_SERIALIZER(AAlphaGameMode)


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaGameMode_h_15_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AAlphaGameMode(AAlphaGameMode&&) = delete; \
	AAlphaGameMode(const AAlphaGameMode&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAlphaGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAlphaGameMode); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AAlphaGameMode) \
	NO_API virtual ~AAlphaGameMode();


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaGameMode_h_12_PROLOG
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaGameMode_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaGameMode_h_15_INCLASS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaGameMode_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AAlphaGameMode;

// ********** End Class AAlphaGameMode *************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaGameMode_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
