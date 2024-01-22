
#include "Effect_Base.h"

// Sets default values
AEffect_Base::AEffect_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_rootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(m_rootComponent);

}

// Called when the game starts or when spawned
void AEffect_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEffect_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

