

#pragma once

#include "CoreMinimal.h"

#include "RPGProject/Unit/UnitAnimInstance.h"
#include "PlayerAnimInstance.generated.h"


UCLASS()
class RPGPROJECT_API UPlayerAnimInstance : public UUnitAnimInstance
{
	GENERATED_BODY()
	
	private: //Attributes
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool _isSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float moveSpeed;

	private: //Components
	class AUnitPlayer* _player;
	int32	_comboCounter;

	public:
	UFUNCTION()
	void AnimNotify_StartAttack();
	UFUNCTION()
	void AnimNotify_EndAttack();

	UFUNCTION()
	void AnimNotify_CheckNextCombo();
	UFUNCTION()
	void AnimNotify_EndCombo();


	public:
	UPlayerAnimInstance();

	// 생성자 다음으로 호출. Unit과 연결되는 시점.
	virtual void NativeInitializeAnimation() override;

	// 월드 생성 시점에 호출. 블루프린트 Preview에서 일어나지 않는다.
	virtual void NativeBeginPlay() override;

	// 매 틱 마다 호출
	virtual void NativeUpdateAnimation(float deltaTime) override;

};
