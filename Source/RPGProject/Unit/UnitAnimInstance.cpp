#include "UnitAnimInstance.h"
#include "../Unit/Unit.h"

UUnitAnimInstance::UUnitAnimInstance() : _unit(nullptr)
{

}

void UUnitAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AUnit *unit = Cast<AUnit>(GetOwningActor());

	if (IsValid(unit))
		_unit = unit;

}

void UUnitAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

}

void UUnitAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	if (IsValid(_unit))
	{

		_isCollapsed = !_unit->GetFalling();

	}
}
