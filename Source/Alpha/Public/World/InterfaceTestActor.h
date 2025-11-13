#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "InterfaceTestActor.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class AAlphaCharacter;

//==========================================================================
// CLASS: AInterfaceTestActor
//==========================================================================
UCLASS()
class ALPHA_API AInterfaceTestActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	//==========================================================================
	// CONSTRUCTOR
	//==========================================================================
	AInterfaceTestActor();

protected:
	//==========================================================================
	// PROTECTED FUNCTIONS
	//==========================================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Interaction Interface
	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteract() override;
	virtual void EndInteract() override;
	virtual void Interact(AAlphaCharacter* PlayerCharacter) override;

	//==========================================================================
	// PROTECTED PROPERTIES
	//==========================================================================
	UPROPERTY(EditAnywhere, Category = "Test Actor")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditInstanceOnly, Category = "Test Actor")
	FInteractableData InstanceInteractableData;
};