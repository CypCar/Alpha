// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UserInterface/Interaction/LootWindowWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeLootWindowWidget() {}

// ********** Begin Cross Module References ********************************************************
ALPHA_API UClass* Z_Construct_UClass_ULootRowWidget_NoRegister();
ALPHA_API UClass* Z_Construct_UClass_ULootWindowWidget();
ALPHA_API UClass* Z_Construct_UClass_ULootWindowWidget_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UMG_API UClass* Z_Construct_UClass_UVerticalBox_NoRegister();
UPackage* Z_Construct_UPackage__Script_Alpha();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ULootWindowWidget ********************************************************
void ULootWindowWidget::StaticRegisterNativesULootWindowWidget()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ULootWindowWidget;
UClass* ULootWindowWidget::GetPrivateStaticClass()
{
	using TClass = ULootWindowWidget;
	if (!Z_Registration_Info_UClass_ULootWindowWidget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("LootWindowWidget"),
			Z_Registration_Info_UClass_ULootWindowWidget.InnerSingleton,
			StaticRegisterNativesULootWindowWidget,
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
	return Z_Registration_Info_UClass_ULootWindowWidget.InnerSingleton;
}
UClass* Z_Construct_UClass_ULootWindowWidget_NoRegister()
{
	return ULootWindowWidget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ULootWindowWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "UserInterface/Interaction/LootWindowWidget.h" },
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/LootWindowWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxVisibleEntries_MetaData[] = {
		{ "Category", "Loot" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Ile wpis\xc3\xb3w ma by\xc4\x87 widocznych jednocze\xc5\x9bnie (starsze usuwamy z do\xc5\x82u)\n" },
#endif
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/LootWindowWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Ile wpis\xc3\xb3w ma by\xc4\x87 widocznych jednocze\xc5\x9bnie (starsze usuwamy z do\xc5\x82u)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EntryLifetime_MetaData[] = {
		{ "Category", "Loot" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Jak d\xc5\x82ugo jeden wpis ma wisie\xc4\x87 (sekundy)\n" },
#endif
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/LootWindowWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Jak d\xc5\x82ugo jeden wpis ma wisie\xc4\x87 (sekundy)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RowClass_MetaData[] = {
		{ "Category", "Loot" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Klasa pojedynczego wiersza\n" },
#endif
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/LootWindowWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Klasa pojedynczego wiersza" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LootListBox_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UserInterface/Interaction/LootWindowWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxVisibleEntries;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EntryLifetime;
	static const UECodeGen_Private::FClassPropertyParams NewProp_RowClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LootListBox;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULootWindowWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULootWindowWidget_Statics::NewProp_MaxVisibleEntries = { "MaxVisibleEntries", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULootWindowWidget, MaxVisibleEntries), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxVisibleEntries_MetaData), NewProp_MaxVisibleEntries_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ULootWindowWidget_Statics::NewProp_EntryLifetime = { "EntryLifetime", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULootWindowWidget, EntryLifetime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EntryLifetime_MetaData), NewProp_EntryLifetime_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ULootWindowWidget_Statics::NewProp_RowClass = { "RowClass", nullptr, (EPropertyFlags)0x0014000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULootWindowWidget, RowClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ULootRowWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RowClass_MetaData), NewProp_RowClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULootWindowWidget_Statics::NewProp_LootListBox = { "LootListBox", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULootWindowWidget, LootListBox), Z_Construct_UClass_UVerticalBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LootListBox_MetaData), NewProp_LootListBox_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULootWindowWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULootWindowWidget_Statics::NewProp_MaxVisibleEntries,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULootWindowWidget_Statics::NewProp_EntryLifetime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULootWindowWidget_Statics::NewProp_RowClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULootWindowWidget_Statics::NewProp_LootListBox,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULootWindowWidget_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ULootWindowWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_Alpha,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULootWindowWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ULootWindowWidget_Statics::ClassParams = {
	&ULootWindowWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ULootWindowWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ULootWindowWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULootWindowWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_ULootWindowWidget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ULootWindowWidget()
{
	if (!Z_Registration_Info_UClass_ULootWindowWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULootWindowWidget.OuterSingleton, Z_Construct_UClass_ULootWindowWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ULootWindowWidget.OuterSingleton;
}
ULootWindowWidget::ULootWindowWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(ULootWindowWidget);
ULootWindowWidget::~ULootWindowWidget() {}
// ********** End Class ULootWindowWidget **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootWindowWidget_h__Script_Alpha_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ULootWindowWidget, ULootWindowWidget::StaticClass, TEXT("ULootWindowWidget"), &Z_Registration_Info_UClass_ULootWindowWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULootWindowWidget), 2278576486U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootWindowWidget_h__Script_Alpha_1789009122(TEXT("/Script/Alpha"),
	Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootWindowWidget_h__Script_Alpha_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Interaction_LootWindowWidget_h__Script_Alpha_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
