// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UserInterface/Interaction/LootRowWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeLootRowWidget() {}

// ********** Begin Cross Module References ********************************************************
ALPHA_API UClass* Z_Construct_UClass_ULootRowWidget();
ALPHA_API UClass* Z_Construct_UClass_ULootRowWidget_NoRegister();
UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_Alpha();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ULootRowWidget ***********************************************************
void ULootRowWidget::StaticRegisterNativesULootRowWidget()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ULootRowWidget;
UClass* ULootRowWidget::GetPrivateStaticClass()
{
	using TClass = ULootRowWidget;
	if (!Z_Registration_Info_UClass_ULootRowWidget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("LootRowWidget"),
			Z_Registration_Info_UClass_ULootRowWidget.InnerSingleton,
			StaticRegisterNativesULootRowWidget,
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
	return Z_Registration_Info_UClass_ULootRowWidget.InnerSingleton;
}
UClass* Z_Construct_UClass_ULootRowWidget_NoRegister()
{
	return ULootRowWidget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ULootRowWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "UserInterface/Interaction/LootRowWidget.h" },
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/LootRowWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NameText_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/LootRowWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_QuantityText_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/LootRowWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NameText;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_QuantityText;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULootRowWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULootRowWidget_Statics::NewProp_NameText = { "NameText", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULootRowWidget, NameText), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NameText_MetaData), NewProp_NameText_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULootRowWidget_Statics::NewProp_QuantityText = { "QuantityText", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULootRowWidget, QuantityText), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_QuantityText_MetaData), NewProp_QuantityText_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULootRowWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULootRowWidget_Statics::NewProp_NameText,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULootRowWidget_Statics::NewProp_QuantityText,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULootRowWidget_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ULootRowWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_Alpha,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULootRowWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ULootRowWidget_Statics::ClassParams = {
	&ULootRowWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ULootRowWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ULootRowWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULootRowWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_ULootRowWidget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ULootRowWidget()
{
	if (!Z_Registration_Info_UClass_ULootRowWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULootRowWidget.OuterSingleton, Z_Construct_UClass_ULootRowWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ULootRowWidget.OuterSingleton;
}
ULootRowWidget::ULootRowWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(ULootRowWidget);
ULootRowWidget::~ULootRowWidget() {}
// ********** End Class ULootRowWidget *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootRowWidget_h__Script_Alpha_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ULootRowWidget, ULootRowWidget::StaticClass, TEXT("ULootRowWidget"), &Z_Registration_Info_UClass_ULootRowWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULootRowWidget), 1195230545U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootRowWidget_h__Script_Alpha_498961910(TEXT("/Script/Alpha"),
	Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootRowWidget_h__Script_Alpha_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootRowWidget_h__Script_Alpha_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
