#pragma once

#include "CoreMinimal.h"
#include "PoolableActor.h"
#include "GameFramework/Actor.h"
#include "DamageActor.generated.h"


class ADamageTextPooler;
class UWD_Text;
class UWidgetComponent;

UCLASS()
class RPGPROJECT_API ADamageActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UWidgetComponent* _widgetComponent;

	UWD_Text* _damageText;

	ADamageTextPooler* _pooler;

public:
	bool IsEnabled = false;
	void DisplayDamage(int32 damage);
	void SetParentPooler(ADamageTextPooler* pooler);
	void ReturnToPooler();
	void SetColor(FColor color);

public:	
	// Sets default values for this actor's properties
ADamageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
