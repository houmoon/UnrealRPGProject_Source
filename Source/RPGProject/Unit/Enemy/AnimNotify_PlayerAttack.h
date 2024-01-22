

#pragma once

#include "CoreMinimal.h"
#include "AnimNotify_PlayNiagaraEffect.h"

#include "AnimNotifyState_TimedNiagaraEffect.h"

#include "AnimNotify_PlayerAttack.generated.h"


UCLASS()
class RPGPROJECT_API UAnimNotify_PlayerAttack : public UAnimNotifyState_TimedNiagaraEffect
{
	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
