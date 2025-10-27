// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AlphaPlayerController.h"

#ifdef ALPHA_AlphaPlayerController_generated_h
#error "AlphaPlayerController.generated.h already included, missing '#pragma once' in AlphaPlayerController.h"
#endif
#define ALPHA_AlphaPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AAlphaPlayerController ***************************************************
ALPHA_API UClass* Z_Construct_UClass_AAlphaPlayerController_NoRegister();

#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaPlayerController_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAAlphaPlayerController(); \
	friend struct Z_Construct_UClass_AAlphaPlayerController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ALPHA_API UClass* Z_Construct_UClass_AAlphaPlayerController_NoRegister(); \
public: \
	DECLARE_CLASS2(AAlphaPlayerController, APlayerController, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/Alpha"), Z_Construct_UClass_AAlphaPlayerController_NoRegister) \
	DECLARE_SERIALIZER(AAlphaPlayerController)


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaPlayerController_h_19_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AAlphaPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	AAlphaPlayerController(AAlphaPlayerController&&) = delete; \
	AAlphaPlayerController(const AAlphaPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAlphaPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAlphaPlayerController); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AAlphaPlayerController) \
	NO_API virtual ~AAlphaPlayerController();


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaPlayerController_h_16_PROLOG
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaPlayerController_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaPlayerController_h_19_INCLASS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaPlayerController_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AAlphaPlayerController;

// ********** End Class AAlphaPlayerController *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
