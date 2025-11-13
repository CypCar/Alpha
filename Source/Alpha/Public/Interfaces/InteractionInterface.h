#pragma once

//==========================================================================
// INCLUDES
//==========================================================================
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

//==========================================================================
// FORWARD DECLARATIONS
//==========================================================================
class AAlphaCharacter;

//==========================================================================
// ENUMS
//==========================================================================
UENUM()
enum class EInteractableType : uint8
{
    Pickup UMETA(DisplayName = "Pickup"),
    NonPlayerCharacter UMETA(DisplayName = "NonPlayerCharacter"),
    Device UMETA(DisplayName = "Device"),
    Toggle UMETA(DisplayName = "Toggle"),
    Container UMETA(DisplayName = "Container")
};

//==========================================================================
// STRUCTS
//==========================================================================
USTRUCT()
struct FInteractableData
{
    GENERATED_USTRUCT_BODY()

    FInteractableData() :
        InteractableType(EInteractableType::Pickup),
        Name(FText::GetEmpty()),
        Action(FText::GetEmpty()),
        Quantity(0),
        InteractionDuration(0.0f)
    {
    }

    UPROPERTY(EditInstanceOnly)
    EInteractableType InteractableType;

    UPROPERTY(EditInstanceOnly)
    FText Name;

    UPROPERTY(EditInstanceOnly)
    FText Action;

    UPROPERTY(EditInstanceOnly)
    int8 Quantity;

    UPROPERTY(EditInstanceOnly)
    float InteractionDuration;
};

//==========================================================================
// INTERFACE
//==========================================================================
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
    GENERATED_BODY()
};

class ALPHA_API IInteractionInterface
{
    GENERATED_BODY()

public:
    //==========================================================================
    // INTERFACE FUNCTIONS
    //==========================================================================
    virtual void BeginFocus();
    virtual void EndFocus();
    virtual void BeginInteract();
    virtual void EndInteract();
    virtual void Interact(AAlphaCharacter* PlayerCharacter);

    //==========================================================================
    // INTERFACE DATA
    //==========================================================================
    FInteractableData InteractableData;
};