// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UserInterface/Inventory/InventoryPanel.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeInventoryPanel() {}

// ********** Begin Cross Module References ********************************************************
ALPHA_API UClass* Z_Construct_UClass_UInventoryPanel();
ALPHA_API UClass* Z_Construct_UClass_UInventoryPanel_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_Alpha();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UInventoryPanel **********************************************************
void UInventoryPanel::StaticRegisterNativesUInventoryPanel()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UInventoryPanel;
UClass* UInventoryPanel::GetPrivateStaticClass()
{
	using TClass = UInventoryPanel;
	if (!Z_Registration_Info_UClass_UInventoryPanel.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("InventoryPanel"),
			Z_Registration_Info_UClass_UInventoryPanel.InnerSingleton,
			StaticRegisterNativesUInventoryPanel,
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
	return Z_Registration_Info_UClass_UInventoryPanel.InnerSingleton;
}
UClass* Z_Construct_UClass_UInventoryPanel_NoRegister()
{
	return UInventoryPanel::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UInventoryPanel_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "UserInterface/Inventory/InventoryPanel.h" },
		{ "ModuleRelativePath", "Public/UserInterface/Inventory/InventoryPanel.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInventoryPanel>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UInventoryPanel_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_Alpha,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryPanel_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInventoryPanel_Statics::ClassParams = {
	&UInventoryPanel::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryPanel_Statics::Class_MetaDataParams), Z_Construct_UClass_UInventoryPanel_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UInventoryPanel()
{
	if (!Z_Registration_Info_UClass_UInventoryPanel.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInventoryPanel.OuterSingleton, Z_Construct_UClass_UInventoryPanel_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInventoryPanel.OuterSingleton;
}
UInventoryPanel::UInventoryPanel(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UInventoryPanel);
UInventoryPanel::~UInventoryPanel() {}
// ********** End Class UInventoryPanel ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryPanel_h__Script_Alpha_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInventoryPanel, UInventoryPanel::StaticClass, TEXT("UInventoryPanel"), &Z_Registration_Info_UClass_UInventoryPanel, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInventoryPanel), 1048792788U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryPanel_h__Script_Alpha_2611164523(TEXT("/Script/Alpha"),
	Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryPanel_h__Script_Alpha_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_Inventory_InventoryPanel_h__Script_Alpha_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
