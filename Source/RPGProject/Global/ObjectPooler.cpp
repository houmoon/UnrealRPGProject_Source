#include "ObjectPooler.h"


AObjectPooler::AObjectPooler()
{
}

void AObjectPooler::Initialize(TSubclassOf<APoolableActor> subClass, int32 size)
{
	for (int32 i = 0; i < size; i++)
	{
		APoolableActor* newObject = GetWorld()->SpawnActor<APoolableActor>(subClass);
		newObject->SetParentPooler(this);
		_poolableActors.Enqueue(newObject);
	}
}

void AObjectPooler::EnqueueActor(APoolableActor* actor)
{
	_poolableActors.Enqueue(actor);
}

APoolableActor* AObjectPooler::GetPooledObject()
{
	APoolableActor* dequeue;

	_poolableActors.Dequeue(dequeue);

	return dequeue;
}

void AObjectPooler::BeginPlay()
{
	Super::BeginPlay();
}
