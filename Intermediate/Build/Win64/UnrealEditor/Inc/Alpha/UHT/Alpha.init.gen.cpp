// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAlpha_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Alpha;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Alpha()
	{
		if (!Z_Registration_Info_UPackage__Script_Alpha.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Alpha",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x7F1C5FAE,
				0x7854E261,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Alpha.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Alpha.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Alpha(Z_Construct_UPackage__Script_Alpha, TEXT("/Script/Alpha"), Z_Registration_Info_UPackage__Script_Alpha, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x7F1C5FAE, 0x7854E261));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
