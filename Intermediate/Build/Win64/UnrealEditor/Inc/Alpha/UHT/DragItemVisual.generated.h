// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "UserInterface/Inventory/DragItemVisual.h"

#ifdef ALPHA_DragItemVisual_generated_h
#error "DragItemVisual.generated.h already included, missing '#pragma once' in DragItemVisual.h"
#endif
#define ALPHA_DragItemVisual_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UDragItemVisual **********************************************************
ALPHA_API UClass* Z_Construct_UClass_UDragItemVisual_NoRegister();

#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_DragItemVisual_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUDragItemVisual(); \
	friend struct Z_Construct_UClass_UDragItemVisual_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ALPHA_API UClass* Z_Construct_UClass_UDragItemVisual_NoRegister(); \
public: \
	DECLARE_CLASS2(UDragItemVisual, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Alpha"), Z_Construct_UClass_UDragItemVisual_NoRegister) \
	DECLARE_SERIALIZER(UDragItemVisual)


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_DragItemVisual_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UDragItemVisual(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDragItemVisual(UDragItemVisual&&) = delete; \
	UDragItemVisual(const UDragItemVisual&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDragItemVisual); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDragItemVisual); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UDragItemVisual) \
	NO_API virtual ~UDragItemVisual();


#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_DragItemVisual_h_13_PROLOG
#define FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_DragItemVisual_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_DragItemVisual_h_16_INCLASS_NO_PURE_DECLS \
	FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_DragItemVisual_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDragItemVisual;

// ********** End Class UDragItemVisual ************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_DragItemVisual_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
