// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Player/MyAlphaPlayerController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeMyAlphaPlayerController() {}

// ********** Begin Cross Module References ********************************************************
ALPHA_API UClass* Z_Construct_UClass_AMyAlphaPlayerController();
ALPHA_API UClass* Z_Construct_UClass_AMyAlphaPlayerController_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
UPackage* Z_Construct_UPackage__Script_Alpha();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AMyAlphaPlayerController *************************************************
void AMyAlphaPlayerController::StaticRegisterNativesAMyAlphaPlayerController()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AMyAlphaPlayerController;
UClass* AMyAlphaPlayerController::GetPrivateStaticClass()
{
	using TClass = AMyAlphaPlayerController;
	if (!Z_Registration_Info_UClass_AMyAlphaPlayerController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("MyAlphaPlayerController"),
			Z_Registration_Info_UClass_AMyAlphaPlayerController.InnerSingleton,
			StaticRegisterNativesAMyAlphaPlayerController,
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
	return Z_Registration_Info_UClass_AMyAlphaPlayerController.InnerSingleton;
}
UClass* Z_Construct_UClass_AMyAlphaPlayerController_NoRegister()
{
	return AMyAlphaPlayerController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AMyAlphaPlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Player/MyAlphaPlayerController.h" },
		{ "ModuleRelativePath", "Public/Player/MyAlphaPlayerController.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyAlphaPlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AMyAlphaPlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_Alpha,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyAlphaPlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyAlphaPlayerController_Statics::ClassParams = {
	&AMyAlphaPlayerController::StaticClass,
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
	0x009003A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMyAlphaPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_AMyAlphaPlayerController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AMyAlphaPlayerController()
{
	if (!Z_Registration_Info_UClass_AMyAlphaPlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyAlphaPlayerController.OuterSingleton, Z_Construct_UClass_AMyAlphaPlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMyAlphaPlayerController.OuterSingleton;
}
AMyAlphaPlayerController::AMyAlphaPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMyAlphaPlayerController);
AMyAlphaPlayerController::~AMyAlphaPlayerController() {}
// ********** End Class AMyAlphaPlayerController ***************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Player_MyAlphaPlayerController_h__Script_Alpha_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMyAlphaPlayerController, AMyAlphaPlayerController::StaticClass, TEXT("AMyAlphaPlayerController"), &Z_Registration_Info_UClass_AMyAlphaPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyAlphaPlayerController), 3126331775U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Player_MyAlphaPlayerController_h__Script_Alpha_3235229058(TEXT("/Script/Alpha"),
	Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Player_MyAlphaPlayerController_h__Script_Alpha_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_Player_MyAlphaPlayerController_h__Script_Alpha_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
