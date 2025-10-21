// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UserInterface/AlphaHUD.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAlphaHUD() {}

// ********** Begin Cross Module References ********************************************************
ALPHA_API UClass* Z_Construct_UClass_AAlphaHUD();
ALPHA_API UClass* Z_Construct_UClass_AAlphaHUD_NoRegister();
ALPHA_API UClass* Z_Construct_UClass_UInteractionWidget_NoRegister();
ALPHA_API UClass* Z_Construct_UClass_UMainMenu_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_AHUD();
UMG_API UClass* Z_Construct_UClass_UUserWidget_NoRegister();
UPackage* Z_Construct_UPackage__Script_Alpha();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AAlphaHUD ****************************************************************
void AAlphaHUD::StaticRegisterNativesAAlphaHUD()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AAlphaHUD;
UClass* AAlphaHUD::GetPrivateStaticClass()
{
	using TClass = AAlphaHUD;
	if (!Z_Registration_Info_UClass_AAlphaHUD.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AlphaHUD"),
			Z_Registration_Info_UClass_AAlphaHUD.InnerSingleton,
			StaticRegisterNativesAAlphaHUD,
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
	return Z_Registration_Info_UClass_AAlphaHUD.InnerSingleton;
}
UClass* Z_Construct_UClass_AAlphaHUD_NoRegister()
{
	return AAlphaHUD::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AAlphaHUD_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "UserInterface/AlphaHUD.h" },
		{ "ModuleRelativePath", "Public/UserInterface/AlphaHUD.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MainMenuClass_MetaData[] = {
		{ "Category", "Widgets" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//==========================================================================\n//PROPERTIES & VARIABELS\n//==========================================================================\n" },
#endif
		{ "ModuleRelativePath", "Public/UserInterface/AlphaHUD.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "PROPERTIES & VARIABELS" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractionWidgetClass_MetaData[] = {
		{ "Category", "Widgets" },
		{ "ModuleRelativePath", "Public/UserInterface/AlphaHUD.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CrosshairWidgetClass_MetaData[] = {
		{ "Category", "Widgets" },
		{ "ModuleRelativePath", "Public/UserInterface/AlphaHUD.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MainMenuWidget_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//==========================================================================\n//PROPERTIES & VARIABELS\n//==========================================================================\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UserInterface/AlphaHUD.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "PROPERTIES & VARIABELS" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractionWidget_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UserInterface/AlphaHUD.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CrosshairWidget_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UserInterface/AlphaHUD.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FClassPropertyParams NewProp_MainMenuClass;
	static const UECodeGen_Private::FClassPropertyParams NewProp_InteractionWidgetClass;
	static const UECodeGen_Private::FClassPropertyParams NewProp_CrosshairWidgetClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MainMenuWidget;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InteractionWidget;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CrosshairWidget;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAlphaHUD>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AAlphaHUD_Statics::NewProp_MainMenuClass = { "MainMenuClass", nullptr, (EPropertyFlags)0x0014000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAlphaHUD, MainMenuClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UMainMenu_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MainMenuClass_MetaData), NewProp_MainMenuClass_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AAlphaHUD_Statics::NewProp_InteractionWidgetClass = { "InteractionWidgetClass", nullptr, (EPropertyFlags)0x0014000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAlphaHUD, InteractionWidgetClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UInteractionWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractionWidgetClass_MetaData), NewProp_InteractionWidgetClass_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AAlphaHUD_Statics::NewProp_CrosshairWidgetClass = { "CrosshairWidgetClass", nullptr, (EPropertyFlags)0x0014000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAlphaHUD, CrosshairWidgetClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CrosshairWidgetClass_MetaData), NewProp_CrosshairWidgetClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAlphaHUD_Statics::NewProp_MainMenuWidget = { "MainMenuWidget", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAlphaHUD, MainMenuWidget), Z_Construct_UClass_UMainMenu_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MainMenuWidget_MetaData), NewProp_MainMenuWidget_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAlphaHUD_Statics::NewProp_InteractionWidget = { "InteractionWidget", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAlphaHUD, InteractionWidget), Z_Construct_UClass_UInteractionWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractionWidget_MetaData), NewProp_InteractionWidget_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAlphaHUD_Statics::NewProp_CrosshairWidget = { "CrosshairWidget", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAlphaHUD, CrosshairWidget), Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CrosshairWidget_MetaData), NewProp_CrosshairWidget_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AAlphaHUD_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAlphaHUD_Statics::NewProp_MainMenuClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAlphaHUD_Statics::NewProp_InteractionWidgetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAlphaHUD_Statics::NewProp_CrosshairWidgetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAlphaHUD_Statics::NewProp_MainMenuWidget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAlphaHUD_Statics::NewProp_InteractionWidget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAlphaHUD_Statics::NewProp_CrosshairWidget,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAlphaHUD_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AAlphaHUD_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AHUD,
	(UObject* (*)())Z_Construct_UPackage__Script_Alpha,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAlphaHUD_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AAlphaHUD_Statics::ClassParams = {
	&AAlphaHUD::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AAlphaHUD_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AAlphaHUD_Statics::PropPointers),
	0,
	0x009003ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AAlphaHUD_Statics::Class_MetaDataParams), Z_Construct_UClass_AAlphaHUD_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AAlphaHUD()
{
	if (!Z_Registration_Info_UClass_AAlphaHUD.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAlphaHUD.OuterSingleton, Z_Construct_UClass_AAlphaHUD_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AAlphaHUD.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AAlphaHUD);
AAlphaHUD::~AAlphaHUD() {}
// ********** End Class AAlphaHUD ******************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_AlphaHUD_h__Script_Alpha_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AAlphaHUD, AAlphaHUD::StaticClass, TEXT("AAlphaHUD"), &Z_Registration_Info_UClass_AAlphaHUD, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAlphaHUD), 4144505331U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_AlphaHUD_h__Script_Alpha_1633881674(TEXT("/Script/Alpha"),
	Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_AlphaHUD_h__Script_Alpha_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_UserInterface_AlphaHUD_h__Script_Alpha_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
