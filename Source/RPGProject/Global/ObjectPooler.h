#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "RPGProject/Actor/PoolableActor.h"
#include "ObjectPooler.generated.h"

UCLASS()
class RPGPROJECT_API AObjectPooler : public AActor
{
	GENERATED_BODY()

public:
	AObjectPooler();
	void Initialize(TSubclassOf<APoolableActor> subClass, int32 size);
	void EnqueueActor(APoolableActor* actor);


	APoolableActor* GetPooledObject();

private:
	TQueue<APoolableActor*> _poolableActors;


	virtual void BeginPlay() override;

};