#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>

#include "Engine/DataTable.h"
#include "AreaActor.generated.h"



UCLASS()
class RPGPROJECT_API AAreaActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UBoxComponent* _boxComp;

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle _rowName;

	private:
	UFUNCTION()
	void onOverlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Sets default values for this actor's properties
	AAreaActor();

};
