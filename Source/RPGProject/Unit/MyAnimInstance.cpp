
#include "MyAnimInstance.h"

#include "DemoChar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

void UMyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();


	_character = Cast<ADemoChar>(GetOwningActor());


}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(_character)
		velocity = _character->GetCharacterMovement()->GetCurrentAcceleration().Size2D();
	

}
