// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UserInterface/Interaction/InteractionWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeInteractionWidget() {}

// ********** Begin Cross Module References ********************************************************
ALPHA_API UClass* Z_Construct_UClass_AAlphaCharacter_NoRegister();
ALPHA_API UClass* Z_Construct_UClass_UInteractionWidget();
ALPHA_API UClass* Z_Construct_UClass_UInteractionWidget_NoRegister();
UMG_API UClass* Z_Construct_UClass_UProgressBar_NoRegister();
UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_Alpha();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UInteractionWidget Function UpdateInteractionProgress ********************
struct Z_Construct_UFunction_UInteractionWidget_UpdateInteractionProgress_Statics
{
	struct InteractionWidget_eventUpdateInteractionProgress_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Interaction Widget | Interactable Data" },
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/InteractionWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UInteractionWidget_UpdateInteractionProgress_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InteractionWidget_eventUpdateInteractionProgress_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UInteractionWidget_UpdateInteractionProgress_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInteractionWidget_UpdateInteractionProgress_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UInteractionWidget_UpdateInteractionProgress_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInteractionWidget_UpdateInteractionProgress_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInteractionWidget, nullptr, "UpdateInteractionProgress", Z_Construct_UFunction_UInteractionWidget_UpdateInteractionProgress_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UInteractionWidget_UpdateInteractionProgress_Statics::PropPointers), sizeof(Z_Construct_UFunction_UInteractionWidget_UpdateInteractionProgress_Statics::InteractionWidget_eventUpdateInteractionProgress_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInteractionWidget_UpdateInteractionProgress_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInteractionWidget_UpdateInteractionProgress_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UInteractionWidget_UpdateInteractionProgress_Statics::InteractionWidget_eventUpdateInteractionProgress_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UInteractionWidget_UpdateInteractionProgress()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInteractionWidget_UpdateInteractionProgress_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInteractionWidget::execUpdateInteractionProgress)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->UpdateInteractionProgress();
	P_NATIVE_END;
}
// ********** End Class UInteractionWidget Function UpdateInteractionProgress **********************

// ********** Begin Class UInteractionWidget *******************************************************
void UInteractionWidget::StaticRegisterNativesUInteractionWidget()
{
	UClass* Class = UInteractionWidget::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "UpdateInteractionProgress", &UInteractionWidget::execUpdateInteractionProgress },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UInteractionWidget;
UClass* UInteractionWidget::GetPrivateStaticClass()
{
	using TClass = UInteractionWidget;
	if (!Z_Registration_Info_UClass_UInteractionWidget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("InteractionWidget"),
			Z_Registration_Info_UClass_UInteractionWidget.InnerSingleton,
			StaticRegisterNativesUInteractionWidget,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UInteractionWidget.InnerSingleton;
}
UClass* Z_Construct_UClass_UInteractionWidget_NoRegister()
{
	return UInteractionWidget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UInteractionWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "UserInterface/Interaction/InteractionWidget.h" },
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/InteractionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerCharacter_MetaData[] = {
		{ "Category", "Interaction Widget | Player Reference" },
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/InteractionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NameText_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "Interaction Widget | Interactable Data" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/InteractionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActionText_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "Interaction Widget | Interactable Data" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/InteractionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_QuantityText_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "Interaction Widget | Interactable Data" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/InteractionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_KeyPressText_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "Interaction Widget | Interactable Data" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/InteractionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractionProgressBar_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "Interaction Widget | Interactable Data" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/InteractionWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentInteractionDuration_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "Interaction Widget | Interactable Data" },
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/InteractionWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerCharacter;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NameText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActionText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_QuantityText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_KeyPressText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InteractionProgressBar;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentInteractionDuration;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UInteractionWidget_UpdateInteractionProgress, "UpdateInteractionProgress" }, // 1705400141
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInteractionWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInteractionWidget_Statics::NewProp_PlayerCharacter = { "PlayerCharacter", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInteractionWidget, PlayerCharacter), Z_Construct_UClass_AAlphaCharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerCharacter_MetaData), NewProp_PlayerCharacter_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInteractionWidget_Statics::NewProp_NameText = { "NameText", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInteractionWidget, NameText), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NameText_MetaData), NewProp_NameText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInteractionWidget_Statics::NewProp_ActionText = { "ActionText", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInteractionWidget, ActionText), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActionText_MetaData), NewProp_ActionText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInteractionWidget_Statics::NewProp_QuantityText = { "QuantityText", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInteractionWidget, QuantityText), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_QuantityText_MetaData), NewProp_QuantityText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInteractionWidget_Statics::NewProp_KeyPressText = { "KeyPressText", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInteractionWidget, KeyPressText), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_KeyPressText_MetaData), NewProp_KeyPressText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInteractionWidget_Statics::NewProp_InteractionProgressBar = { "InteractionProgressBar", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInteractionWidget, InteractionProgressBar), Z_Construct_UClass_UProgressBar_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractionProgressBar_MetaData), NewProp_InteractionProgressBar_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UInteractionWidget_Statics::NewProp_CurrentInteractionDuration = { "CurrentInteractionDuration", nullptr, (EPropertyFlags)0x0020080000020001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInteractionWidget, CurrentInteractionDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentInteractionDuration_MetaData), NewProp_CurrentInteractionDuration_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UInteractionWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInteractionWidget_Statics::NewProp_PlayerCharacter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInteractionWidget_Statics::NewProp_NameText,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInteractionWidget_Statics::NewProp_ActionText,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInteractionWidget_Statics::NewProp_QuantityText,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInteractionWidget_Statics::NewProp_KeyPressText,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInteractionWidget_Statics::NewProp_InteractionProgressBar,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInteractionWidget_Statics::NewProp_CurrentInteractionDuration,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInteractionWidget_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UInteractionWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_Alpha,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInteractionWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInteractionWidget_Statics::ClassParams = {
	&UInteractionWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UInteractionWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UInteractionWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInteractionWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UInteractionWidget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UInteractionWidget()
{
	if (!Z_Registration_Info_UClass_UInteractionWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInteractionWidget.OuterSingleton, Z_Construct_UClass_UInteractionWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInteractionWidget.OuterSingleton;
}
UInteractionWidget::UInteractionWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UInteractionWidget);
UInteractionWidget::~UInteractionWidget() {}
// ********** End Class UInteractionWidget *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_InteractionWidget_h__Script_Alpha_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInteractionWidget, UInteractionWidget::StaticClass, TEXT("UInteractionWidget"), &Z_Registration_Info_UClass_UInteractionWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInteractionWidget), 3830260574U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_InteractionWidget_h__Script_Alpha_4015618896(TEXT("/Script/Alpha"),
	Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_InteractionWidget_h__Script_Alpha_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_InteractionWidget_h__Script_Alpha_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
