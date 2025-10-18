// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Player/MyAlphaPlayerController.h"

#ifdef ALPHA_MyAlphaPlayerController_generated_h
#error "MyAlphaPlayerController.generated.h already included, missing '#pragma once' in MyAlphaPlayerController.h"
#endif
#define ALPHA_MyAlphaPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AMyAlphaPlayerController *************************************************
ALPHA_API UClass* Z_Construct_UClass_AMyAlphaPlayerController_NoRegister();

#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Player_MyAlphaPlayerController_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMyAlphaPlayerController(); \
	friend struct Z_Construct_UClass_AMyAlphaPlayerController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ALPHA_API UClass* Z_Construct_UClass_AMyAlphaPlayerController_NoRegister(); \
public: \
	DECLARE_CLASS2(AMyAlphaPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Alpha"), Z_Construct_UClass_AMyAlphaPlayerController_NoRegister) \
	DECLARE_SERIALIZER(AMyAlphaPlayerController)


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Player_MyAlphaPlayerController_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AMyAlphaPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	AMyAlphaPlayerController(AMyAlphaPlayerController&&) = delete; \
	AMyAlphaPlayerController(const AMyAlphaPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMyAlphaPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMyAlphaPlayerController); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AMyAlphaPlayerController) \
	NO_API virtual ~AMyAlphaPlayerController();


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Player_MyAlphaPlayerController_h_12_PROLOG
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Player_MyAlphaPlayerController_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Player_MyAlphaPlayerController_h_15_INCLASS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Player_MyAlphaPlayerController_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AMyAlphaPlayerController;

// ********** End Class AMyAlphaPlayerController ***************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Player_MyAlphaPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
