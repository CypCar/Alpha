#include "World/InterfaceTestActor.h"

//==========================================================================
// CONSTRUCTOR
//==========================================================================
AInterfaceTestActor::AInterfaceTestActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Component Setup
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	// Collision Setup for Interaction System
	Mesh->SetCollisionObjectType(ECC_GameTraceChannel1);
}

//==========================================================================
// GAME FLOW
//==========================================================================
void AInterfaceTestActor::BeginPlay()
{
	Super::BeginPlay();
	InteractableData = InstanceInteractableData;
}

void AInterfaceTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//==========================================================================
// INTERACTION INTERFACE IMPLEMENTATION
//==========================================================================
void AInterfaceTestActor::BeginFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(true);
	}
	UE_LOG(LogTemp, Warning, TEXT("Calling BeginFocus override on interface test actor."));
}

void AInterfaceTestActor::EndFocus()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(false);
	}
	UE_LOG(LogTemp, Warning, TEXT("Calling EndFocus override on interface test actor."));
}

void AInterfaceTestActor::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling BeginInteract override on interface test actor."));
}

void AInterfaceTestActor::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling EndInteract override on interface test actor."));
}

void AInterfaceTestActor::Interact(AAlphaCharacter* PlayerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Interact override on interface test actor."));
}