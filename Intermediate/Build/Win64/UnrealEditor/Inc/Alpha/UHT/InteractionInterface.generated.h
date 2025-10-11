// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Interfaces/InteractionInterface.h"

#ifdef ALPHA_InteractionInterface_generated_h
#error "InteractionInterface.generated.h already included, missing '#pragma once' in InteractionInterface.h"
#endif
#define ALPHA_InteractionInterface_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Interface UInteractionInterface ************************************************
ALPHA_API UClass* Z_Construct_UClass_UInteractionInterface_NoRegister();

#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Interfaces_InteractionInterface_h_13_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	ALPHA_API UInteractionInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UInteractionInterface(UInteractionInterface&&) = delete; \
	UInteractionInterface(const UInteractionInterface&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(ALPHA_API, UInteractionInterface); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInteractionInterface); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInteractionInterface) \
	virtual ~UInteractionInterface() = default;


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Interfaces_InteractionInterface_h_13_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUInteractionInterface(); \
	friend struct Z_Construct_UClass_UInteractionInterface_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ALPHA_API UClass* Z_Construct_UClass_UInteractionInterface_NoRegister(); \
public: \
	DECLARE_CLASS2(UInteractionInterface, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/Alpha"), Z_Construct_UClass_UInteractionInterface_NoRegister) \
	DECLARE_SERIALIZER(UInteractionInterface)


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Interfaces_InteractionInterface_h_13_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Interfaces_InteractionInterface_h_13_GENERATED_UINTERFACE_BODY() \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Interfaces_InteractionInterface_h_13_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Interfaces_InteractionInterface_h_13_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~IInteractionInterface() {} \
public: \
	typedef UInteractionInterface UClassType; \
	typedef IInteractionInterface ThisClass; \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Interfaces_InteractionInterface_h_10_PROLOG
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Interfaces_InteractionInterface_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Interfaces_InteractionInterface_h_13_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UInteractionInterface;

// ********** End Interface UInteractionInterface **************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Interfaces_InteractionInterface_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
