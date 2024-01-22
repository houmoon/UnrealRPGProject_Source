#include "PoolableActor.h"

#include "RPGProject/Global/ObjectPooler.h"

void APoolableActor::SetParentPooler(AObjectPooler* pooler)
{
	_pooler = pooler;
}

void APoolableActor::ReturnToPooler()
{
	if(_pooler)
		_pooler->EnqueueActor(this);
}

APoolableActor::APoolableActor()
{
}

void APoolableActor::BeginPlay()
{
	Super::BeginPlay();
}

void APoolableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
