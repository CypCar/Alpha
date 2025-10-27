// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AlphaCharacter.h"

#ifdef ALPHA_AlphaCharacter_generated_h
#error "AlphaCharacter.generated.h already included, missing '#pragma once' in AlphaCharacter.h"
#endif
#define ALPHA_AlphaCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FInteractionData **************************************************
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaCharacter_h_21_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FInteractionData_Statics; \
	ALPHA_API static class UScriptStruct* StaticStruct();


struct FInteractionData;
// ********** End ScriptStruct FInteractionData ****************************************************

// ********** Begin Class AAlphaCharacter **********************************************************
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaCharacter_h_42_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDoJumpEnd); \
	DECLARE_FUNCTION(execDoJumpStart); \
	DECLARE_FUNCTION(execDoLook); \
	DECLARE_FUNCTION(execDoMove);


ALPHA_API UClass* Z_Construct_UClass_AAlphaCharacter_NoRegister();

#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaCharacter_h_42_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAAlphaCharacter(); \
	friend struct Z_Construct_UClass_AAlphaCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ALPHA_API UClass* Z_Construct_UClass_AAlphaCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(AAlphaCharacter, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/Alpha"), Z_Construct_UClass_AAlphaCharacter_NoRegister) \
	DECLARE_SERIALIZER(AAlphaCharacter)


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaCharacter_h_42_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AAlphaCharacter(AAlphaCharacter&&) = delete; \
	AAlphaCharacter(const AAlphaCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAlphaCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAlphaCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AAlphaCharacter) \
	NO_API virtual ~AAlphaCharacter();


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaCharacter_h_39_PROLOG
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaCharacter_h_42_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaCharacter_h_42_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaCharacter_h_42_INCLASS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaCharacter_h_42_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AAlphaCharacter;

// ********** End Class AAlphaCharacter ************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
