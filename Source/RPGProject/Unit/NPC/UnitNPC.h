#pragma once

#include "CoreMinimal.h"
#include "RPGProject/Interfaces/Interactable.h"
#include "RPGProject/Unit/Unit.h"
#include "UnitNPC.generated.h"

class UNPCModelComponent;

UCLASS()
class RPGPROJECT_API AUnitNPC : public AUnit, public IInteractable
{
	GENERATED_BODY()

	public:
	AUnitNPC();

	protected:
	virtual void BeginPlay() override;

	public:
	virtual void Tick(float DeltaTime) override;


	public: //Getters

	public: //Delegates

	public: //Messeages
	virtual void OnEnterOverlap() override;
	virtual void OnInteract() override;
	virtual void OnExitOverlap() override;

	private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UNPCModelComponent* _model;

};