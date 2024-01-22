#include "DamageTextPooler.h"

ADamageTextPooler* ADamageTextPooler::_instance = nullptr;

ADamageTextPooler* ADamageTextPooler::GetInstance()
{
	return _instance;
}

ADamageTextPooler::ADamageTextPooler()
{
}

ADamageActor* ADamageTextPooler::GetPooledObject()
{
	for(int32 i=0; i<_size; i++)
	{
		if(!_poolableActors[i]->IsEnabled)
		{
			_poolableActors[i]->IsEnabled = true;
			return _poolableActors[i];
		}
			
	}

	return nullptr;
}

void ADamageTextPooler::BeginPlay()
{
	Super::BeginPlay();

	_instance = this;

	for (int32 i = 0; i < _size; i++)
	{
		ADamageActor* newObject = GetWorld()->SpawnActor<ADamageActor>(_subClass);
		newObject->SetActorLocation(GetActorLocation());
		newObject->SetParentPooler(this);
		_poolableActors.Add(newObject);
	}
}
