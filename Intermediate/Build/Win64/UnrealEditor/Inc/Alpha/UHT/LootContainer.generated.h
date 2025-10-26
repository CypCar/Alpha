// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "World/LootContainer.h"

#ifdef ALPHA_LootContainer_generated_h
#error "LootContainer.generated.h already included, missing '#pragma once' in LootContainer.h"
#endif
#define ALPHA_LootContainer_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ALootContainer ***********************************************************
ALPHA_API UClass* Z_Construct_UClass_ALootContainer_NoRegister();

#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_World_LootContainer_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesALootContainer(); \
	friend struct Z_Construct_UClass_ALootContainer_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ALPHA_API UClass* Z_Construct_UClass_ALootContainer_NoRegister(); \
public: \
	DECLARE_CLASS2(ALootContainer, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Alpha"), Z_Construct_UClass_ALootContainer_NoRegister) \
	DECLARE_SERIALIZER(ALootContainer) \
	virtual UObject* _getUObject() const override { return const_cast<ALootContainer*>(this); }


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_World_LootContainer_h_14_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ALootContainer(ALootContainer&&) = delete; \
	ALootContainer(const ALootContainer&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALootContainer); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALootContainer); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ALootContainer) \
	NO_API virtual ~ALootContainer();


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_World_LootContainer_h_11_PROLOG
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_World_LootContainer_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_World_LootContainer_h_14_INCLASS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_World_LootContainer_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ALootContainer;

// ********** End Class ALootContainer *************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_World_LootContainer_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
