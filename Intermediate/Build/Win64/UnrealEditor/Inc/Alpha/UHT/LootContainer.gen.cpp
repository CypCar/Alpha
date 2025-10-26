// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "World/LootContainer.h"
#include "Engine/DataTable.h"
#include "Interfaces/InteractionInterface.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeLootContainer() {}

// ********** Begin Cross Module References ********************************************************
ALPHA_API UClass* Z_Construct_UClass_ALootContainer();
ALPHA_API UClass* Z_Construct_UClass_ALootContainer_NoRegister();
ALPHA_API UClass* Z_Construct_UClass_UInteractionInterface_NoRegister();
ALPHA_API UClass* Z_Construct_UClass_UItemBase_NoRegister();
ALPHA_API UScriptStruct* Z_Construct_UScriptStruct_FInteractableData();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FDataTableRowHandle();
UPackage* Z_Construct_UPackage__Script_Alpha();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ALootContainer ***********************************************************
void ALootContainer::StaticRegisterNativesALootContainer()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ALootContainer;
UClass* ALootContainer::GetPrivateStaticClass()
{
	using TClass = ALootContainer;
	if (!Z_Registration_Info_UClass_ALootContainer.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("LootContainer"),
			Z_Registration_Info_UClass_ALootContainer.InnerSingleton,
			StaticRegisterNativesALootContainer,
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
	return Z_Registration_Info_UClass_ALootContainer.InnerSingleton;
}
UClass* Z_Construct_UClass_ALootContainer_NoRegister()
{
	return ALootContainer::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ALootContainer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "World/LootContainer.h" },
		{ "ModuleRelativePath", "Public/World/LootContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ContainerMesh_MetaData[] = {
		{ "Category", "Container | Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//==========================================================================\n//PROPERTIES & VARIABELS\n//==========================================================================\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/World/LootContainer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "PROPERTIES & VARIABELS" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemReference_MetaData[] = {
		{ "Category", "Container | Item Reference" },
		{ "ModuleRelativePath", "Public/World/LootContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOneTimeLoot_MetaData[] = {
		{ "Category", "Container | Behavior" },
		{ "ModuleRelativePath", "Public/World/LootContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDestroyOnEmpty_MetaData[] = {
		{ "Category", "Container | Behavior" },
		{ "ModuleRelativePath", "Public/World/LootContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOpened_MetaData[] = {
		{ "Category", "Container | State" },
		{ "ModuleRelativePath", "Public/World/LootContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InstanceInteractableData_MetaData[] = {
		{ "Category", "Container | Interaction" },
		{ "ModuleRelativePath", "Public/World/LootContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemQuantity_MetaData[] = {
		{ "Category", "Container | Item Initialization" },
		{ "ModuleRelativePath", "Public/World/LootContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemRowHandle_MetaData[] = {
		{ "Category", "Container | Item Initialization" },
		{ "ModuleRelativePath", "Public/World/LootContainer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ContainerDisplayName_MetaData[] = {
		{ "Category", "Container | UI" },
		{ "ModuleRelativePath", "Public/World/LootContainer.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ContainerMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ItemReference;
	static void NewProp_bOneTimeLoot_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOneTimeLoot;
	static void NewProp_bDestroyOnEmpty_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDestroyOnEmpty;
	static void NewProp_bOpened_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOpened;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InstanceInteractableData;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ItemQuantity;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ItemRowHandle;
	static const UECodeGen_Private::FTextPropertyParams NewProp_ContainerDisplayName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALootContainer>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALootContainer_Statics::NewProp_ContainerMesh = { "ContainerMesh", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALootContainer, ContainerMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ContainerMesh_MetaData), NewProp_ContainerMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALootContainer_Statics::NewProp_ItemReference = { "ItemReference", nullptr, (EPropertyFlags)0x0020080000020001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALootContainer, ItemReference), Z_Construct_UClass_UItemBase_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemReference_MetaData), NewProp_ItemReference_MetaData) };
void Z_Construct_UClass_ALootContainer_Statics::NewProp_bOneTimeLoot_SetBit(void* Obj)
{
	((ALootContainer*)Obj)->bOneTimeLoot = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ALootContainer_Statics::NewProp_bOneTimeLoot = { "bOneTimeLoot", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ALootContainer), &Z_Construct_UClass_ALootContainer_Statics::NewProp_bOneTimeLoot_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOneTimeLoot_MetaData), NewProp_bOneTimeLoot_MetaData) };
void Z_Construct_UClass_ALootContainer_Statics::NewProp_bDestroyOnEmpty_SetBit(void* Obj)
{
	((ALootContainer*)Obj)->bDestroyOnEmpty = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ALootContainer_Statics::NewProp_bDestroyOnEmpty = { "bDestroyOnEmpty", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ALootContainer), &Z_Construct_UClass_ALootContainer_Statics::NewProp_bDestroyOnEmpty_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDestroyOnEmpty_MetaData), NewProp_bDestroyOnEmpty_MetaData) };
void Z_Construct_UClass_ALootContainer_Statics::NewProp_bOpened_SetBit(void* Obj)
{
	((ALootContainer*)Obj)->bOpened = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ALootContainer_Statics::NewProp_bOpened = { "bOpened", nullptr, (EPropertyFlags)0x0020080000020801, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ALootContainer), &Z_Construct_UClass_ALootContainer_Statics::NewProp_bOpened_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOpened_MetaData), NewProp_bOpened_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ALootContainer_Statics::NewProp_InstanceInteractableData = { "InstanceInteractableData", nullptr, (EPropertyFlags)0x0020080000020801, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALootContainer, InstanceInteractableData), Z_Construct_UScriptStruct_FInteractableData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InstanceInteractableData_MetaData), NewProp_InstanceInteractableData_MetaData) }; // 171235710
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ALootContainer_Statics::NewProp_ItemQuantity = { "ItemQuantity", nullptr, (EPropertyFlags)0x0020080000000801, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALootContainer, ItemQuantity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemQuantity_MetaData), NewProp_ItemQuantity_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ALootContainer_Statics::NewProp_ItemRowHandle = { "ItemRowHandle", nullptr, (EPropertyFlags)0x0020080000000801, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALootContainer, ItemRowHandle), Z_Construct_UScriptStruct_FDataTableRowHandle, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemRowHandle_MetaData), NewProp_ItemRowHandle_MetaData) }; // 4101738896
const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_ALootContainer_Statics::NewProp_ContainerDisplayName = { "ContainerDisplayName", nullptr, (EPropertyFlags)0x0020080000000801, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALootContainer, ContainerDisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ContainerDisplayName_MetaData), NewProp_ContainerDisplayName_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ALootContainer_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALootContainer_Statics::NewProp_ContainerMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALootContainer_Statics::NewProp_ItemReference,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALootContainer_Statics::NewProp_bOneTimeLoot,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALootContainer_Statics::NewProp_bDestroyOnEmpty,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALootContainer_Statics::NewProp_bOpened,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALootContainer_Statics::NewProp_InstanceInteractableData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALootContainer_Statics::NewProp_ItemQuantity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALootContainer_Statics::NewProp_ItemRowHandle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALootContainer_Statics::NewProp_ContainerDisplayName,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALootContainer_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ALootContainer_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Alpha,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALootContainer_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_ALootContainer_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UInteractionInterface_NoRegister, (int32)VTABLE_OFFSET(ALootContainer, IInteractionInterface), false },  // 476134757
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_ALootContainer_Statics::ClassParams = {
	&ALootContainer::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ALootContainer_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ALootContainer_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ALootContainer_Statics::Class_MetaDataParams), Z_Construct_UClass_ALootContainer_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ALootContainer()
{
	if (!Z_Registration_Info_UClass_ALootContainer.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ALootContainer.OuterSingleton, Z_Construct_UClass_ALootContainer_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ALootContainer.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ALootContainer);
ALootContainer::~ALootContainer() {}
// ********** End Class ALootContainer *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_World_LootContainer_h__Script_Alpha_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ALootContainer, ALootContainer::StaticClass, TEXT("ALootContainer"), &Z_Registration_Info_UClass_ALootContainer, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALootContainer), 2077478883U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_World_LootContainer_h__Script_Alpha_1426381652(TEXT("/Script/Alpha"),
	Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_World_LootContainer_h__Script_Alpha_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_antek_Documents_Unreal_Projects_Alpha_Source_Alpha_Public_World_LootContainer_h__Script_Alpha_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
