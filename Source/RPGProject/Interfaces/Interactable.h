#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};


class RPGPROJECT_API IInteractable
{
	GENERATED_BODY()
	public:
	virtual void OnEnterOverlap() = 0;

	virtual void OnInteract() = 0;

	virtual void OnExitOverlap() = 0;

};
