#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "DamageActor.h"
#include "DamageTextPooler.generated.h"

UCLASS()
class RPGPROJECT_API ADamageTextPooler : public AActor
{
	GENERATED_BODY()

public:
	static ADamageTextPooler* GetInstance();

	ADamageTextPooler();
	void EnqueueActor(ADamageActor* actor);


	ADamageActor* GetPooledObject();

private:
	static ADamageTextPooler* _instance;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<ADamageActor> _subClass;


	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	int32 _size;

	UPROPERTY()
	TArray<ADamageActor*> _poolableActors;


	virtual void BeginPlay() override;

};