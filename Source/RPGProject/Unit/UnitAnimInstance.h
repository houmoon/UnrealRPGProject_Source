#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UnitAnimInstance.generated.h"

UCLASS()
class RPGPROJECT_API UUnitAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	protected: //Attributes
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool _isMoving;

	private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool _isCollapsed;

	private: //Components
	class AUnit* _unit;

	public:
	UUnitAnimInstance();

	// 생성자 다음으로 호출. Unit과 연결되는 시점.
	virtual void NativeInitializeAnimation() override;

	// 월드 생성 시점에 호출. 블루프린트 Preview에서 일어나지 않는다.
	virtual void NativeBeginPlay() override;

	// 매 틱 마다 호출
	virtual void NativeUpdateAnimation(float deltaTime) override;

};
