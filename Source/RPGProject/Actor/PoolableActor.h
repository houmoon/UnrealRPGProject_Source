#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolableActor.generated.h"


class AObjectPooler;

UCLASS()
class RPGPROJECT_API APoolableActor : public AActor
{
	GENERATED_BODY()

	AObjectPooler* _pooler;

	public:
	void SetParentPooler(AObjectPooler* pooler);
	void ReturnToPooler();


	// Sets default values for this actor's properties
	APoolableActor();

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
