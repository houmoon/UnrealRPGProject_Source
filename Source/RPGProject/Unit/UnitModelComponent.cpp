#include "UnitModelComponent.h"

#include "RPGProject/Actor/DamageTextPooler.h"

void UUnitModelComponent::Damage(int32 damage)
{
	
}

// Sets default values for this component's properties
UUnitModelComponent::UUnitModelComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UUnitModelComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void UUnitModelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UUnitModelComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

