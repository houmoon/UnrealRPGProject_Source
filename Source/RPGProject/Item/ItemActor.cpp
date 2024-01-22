


#include "ItemActor.h"

#include "Item.h"
#include "../Global/ItemManager.h"
#include "Components/SphereComponent.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"

void AItemActor::onBeginOverlap(UPrimitiveComponent* _primitiveComp, AActor* _otherActor, UPrimitiveComponent* _otherPrimitiveComp, int32 _index, bool _bFromSweep, const FHitResult& _hitInfo)
{
	_item = ItemManager::GetInstance()->MakeItem(FCString::Atoi(*_dataBase.RowName.ToString()));

	AUnitPlayer* player = Cast<AUnitPlayer>(_otherActor);
	if(nullptr != player)
	{
		player->AddItem(_item);
		Destroy();
	}
}

// Sets default values
AItemActor::AItemActor()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));

	SetRootComponent(_sphere);

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	_sphere->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::onBeginOverlap);
}

void AItemActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

