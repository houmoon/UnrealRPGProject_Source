
#include "AnimNotify_PlayerAttack.h"

#include "RPGProject/Unit/Player/UnitPlayer.h"

void UAnimNotify_PlayerAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AUnitPlayer* player = Cast<AUnitPlayer>(MeshComp->GetOwner());

	if(IsValid(player))
	{
		player->SetWeaponOverlap(true);
	}
}

void UAnimNotify_PlayerAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AUnitPlayer* player = Cast<AUnitPlayer>(MeshComp->GetOwner());

	if (IsValid(player))
	{
		player->SetWeaponOverlap(false);
	}

}
