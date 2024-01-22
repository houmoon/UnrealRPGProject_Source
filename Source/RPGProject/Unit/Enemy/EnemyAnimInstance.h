

#pragma once

#include "CoreMinimal.h"
#include "RPGProject/Enums/UnitEnums.h"

#include "RPGProject/Unit/UnitAnimInstance.h"
#include "EnemyAnimInstance.generated.h"


UCLASS()
class RPGPROJECT_API UEnemyAnimInstance : public UUnitAnimInstance
{
	GENERATED_BODY()

	private: //Attributes

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EENEMY_STATE _state;

	class AUnitEnemy*	_enemy;

	public:
	UFUNCTION()
	void AnimNotify_DamageToTarget();

	UFUNCTION()
	void AnimNotify_Burn();

	UFUNCTION()
	void AnimNotify_GiveItem();

	public:
	UEnemyAnimInstance();

	// 생성자 다음으로 호출. Unit과 연결되는 시점.
	virtual void NativeInitializeAnimation() override;

	// 월드 생성 시점에 호출. 블루프린트 Preview에서 일어나지 않는다.
	virtual void NativeBeginPlay() override;

	// 매 틱 마다 호출
	virtual void NativeUpdateAnimation(float deltaTime) override;

};
