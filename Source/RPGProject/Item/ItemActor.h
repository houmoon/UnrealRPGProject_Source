

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"


UCLASS()
class RPGPROJECT_API AItemActor : public AActor
{
	GENERATED_BODY()

	private:
	//충돌체
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USphereComponent* _sphere;

	//스테틱 메시
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* _staticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data", meta = (RowType = "ItemData", AllowPrivateAccess = "true"))
	FDataTableRowHandle _dataBase;

	Item* _item;

private:
	UFUNCTION()
	void onBeginOverlap(UPrimitiveComponent* _primitiveComp, AActor* _otherActor, UPrimitiveComponent* _otherPrimitiveComp, int32 _index, bool _bFromSweep, const FHitResult& _hitInfo);

public:	
	// Sets default values for this actor's properties
	AItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
