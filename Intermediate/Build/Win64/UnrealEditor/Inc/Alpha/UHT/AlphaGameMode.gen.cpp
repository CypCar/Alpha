// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Alpha/AlphaGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAlphaGameMode() {}

// ********** Begin Cross Module References ********************************************************
ALPHA_API UClass* Z_Construct_UClass_AAlphaGameMode();
ALPHA_API UClass* Z_Construct_UClass_AAlphaGameMode_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
UPackage* Z_Construct_UPackage__Script_Alpha();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AAlphaGameMode ***********************************************************
void AAlphaGameMode::StaticRegisterNativesAAlphaGameMode()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AAlphaGameMode;
UClass* AAlphaGameMode::GetPrivateStaticClass()
{
	using TClass = AAlphaGameMode;
	if (!Z_Registration_Info_UClass_AAlphaGameMode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AlphaGameMode"),
			Z_Registration_Info_UClass_AAlphaGameMode.InnerSingleton,
			StaticRegisterNativesAAlphaGameMode,
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
	return Z_Registration_Info_UClass_AAlphaGameMode.InnerSingleton;
}
UClass* Z_Construct_UClass_AAlphaGameMode_NoRegister()
{
	return AAlphaGameMode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AAlphaGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple GameMode for a third person game\n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "AlphaGameMode.h" },
		{ "ModuleRelativePath", "AlphaGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple GameMode for a third person game" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAlphaGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AAlphaGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_Alpha,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAlphaGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AAlphaGameMode_Statics::ClassParams = {
	&AAlphaGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008003ADu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AAlphaGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AAlphaGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AAlphaGameMode()
{
	if (!Z_Registration_Info_UClass_AAlphaGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAlphaGameMode.OuterSingleton, Z_Construct_UClass_AAlphaGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AAlphaGameMode.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AAlphaGameMode);
AAlphaGameMode::~AAlphaGameMode() {}
// ********** End Class AAlphaGameMode *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaGameMode_h__Script_Alpha_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AAlphaGameMode, AAlphaGameMode::StaticClass, TEXT("AAlphaGameMode"), &Z_Registration_Info_UClass_AAlphaGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAlphaGameMode), 503514535U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaGameMode_h__Script_Alpha_1245347491(TEXT("/Script/Alpha"),
	Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaGameMode_h__Script_Alpha_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_AlphaGameMode_h__Script_Alpha_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
