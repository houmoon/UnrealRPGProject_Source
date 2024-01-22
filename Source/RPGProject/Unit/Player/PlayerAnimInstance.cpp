#include "PlayerAnimInstance.h"

#include "UnitPlayer.h"

void UPlayerAnimInstance::AnimNotify_StartAttack()
{
	_player->SetWeaponOverlap(true);
}

void UPlayerAnimInstance::AnimNotify_EndAttack()
{
	_player->SetWeaponOverlap(false );
}

void UPlayerAnimInstance::AnimNotify_CheckNextCombo()
{
	
}

void UPlayerAnimInstance::AnimNotify_EndCombo()
{
	if(_player->IsNextCombo)
	{
		_player->IsNextCombo = false;
		_comboCounter++;

		//분기에 따라 콤보 Jump
		Montage_Play(GetCurrentActiveMontage());
		Montage_JumpToSection(FName(FString::Printf(TEXT("Combo%d"), _comboCounter)));
		
	}
	else
	{
		_player->IsAttacking = false;
		_comboCounter = 0;
		_player->IsNextCombo = false;
		Montage_Stop(0.25f);
	}
}

UPlayerAnimInstance::UPlayerAnimInstance()
{
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AUnitPlayer* pPlayer = Cast<AUnitPlayer>(GetOwningActor());

	if (IsValid(pPlayer))
		_player = pPlayer;
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	if (IsValid(_player))
	{
		moveSpeed = _player->GetCurrentMoveSpeed();

		bool acceling = _player->GetAcceling();
		bool moving = 0.f < moveSpeed;
		bool sprinting = _player->GetSprintSpeed() - 0.1f <= _player->GetCurrentMoveSpeed();

		_isMoving = moving && acceling;
		_isSprinting = sprinting && acceling;

	}
}
