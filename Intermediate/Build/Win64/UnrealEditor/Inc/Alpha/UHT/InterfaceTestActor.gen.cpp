// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "World/InterfaceTestActor.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeInterfaceTestActor() {}

// ********** Begin Cross Module References ********************************************************
ALPHA_API UClass* Z_Construct_UClass_AInterfaceTestActor();
ALPHA_API UClass* Z_Construct_UClass_AInterfaceTestActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AActor();
UPackage* Z_Construct_UPackage__Script_Alpha();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AInterfaceTestActor ******************************************************
void AInterfaceTestActor::StaticRegisterNativesAInterfaceTestActor()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AInterfaceTestActor;
UClass* AInterfaceTestActor::GetPrivateStaticClass()
{
	using TClass = AInterfaceTestActor;
	if (!Z_Registration_Info_UClass_AInterfaceTestActor.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("InterfaceTestActor"),
			Z_Registration_Info_UClass_AInterfaceTestActor.InnerSingleton,
			StaticRegisterNativesAInterfaceTestActor,
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
	return Z_Registration_Info_UClass_AInterfaceTestActor.InnerSingleton;
}
UClass* Z_Construct_UClass_AInterfaceTestActor_NoRegister()
{
	return AInterfaceTestActor::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AInterfaceTestActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "World/InterfaceTestActor.h" },
		{ "ModuleRelativePath", "Public/World/InterfaceTestActor.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AInterfaceTestActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AInterfaceTestActor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Alpha,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInterfaceTestActor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AInterfaceTestActor_Statics::ClassParams = {
	&AInterfaceTestActor::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AInterfaceTestActor_Statics::Class_MetaDataParams), Z_Construct_UClass_AInterfaceTestActor_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AInterfaceTestActor()
{
	if (!Z_Registration_Info_UClass_AInterfaceTestActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AInterfaceTestActor.OuterSingleton, Z_Construct_UClass_AInterfaceTestActor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AInterfaceTestActor.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AInterfaceTestActor);
AInterfaceTestActor::~AInterfaceTestActor() {}
// ********** End Class AInterfaceTestActor ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_World_InterfaceTestActor_h__Script_Alpha_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AInterfaceTestActor, AInterfaceTestActor::StaticClass, TEXT("AInterfaceTestActor"), &Z_Registration_Info_UClass_AInterfaceTestActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AInterfaceTestActor), 3881843790U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_World_InterfaceTestActor_h__Script_Alpha_2853317277(TEXT("/Script/Alpha"),
	Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_World_InterfaceTestActor_h__Script_Alpha_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_World_InterfaceTestActor_h__Script_Alpha_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
