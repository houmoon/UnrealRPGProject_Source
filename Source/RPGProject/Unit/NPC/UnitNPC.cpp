#include "UnitNPC.h"
#include "NPCModelComponent.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/Unit/Player/UnitPlayer.h"


AUnitNPC::AUnitNPC()
{
	_model = CreateDefaultSubobject<UNPCModelComponent>(TEXT("NPC Model"));

}

void AUnitNPC::BeginPlay()
{
	Super::BeginPlay();

	_model->Init(GetWorld());
}



void AUnitNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnitNPC::OnEnterOverlap()
{
	GetMesh()->CustomDepthStencilValue = 1;
	GetMesh()->MarkRenderStateDirty();
}

void AUnitNPC::OnInteract()
{
	AUnitPlayer* player = AUnitPlayer::CurrentPlayer;

	if(player)
	{
		player->StartDialogue(this, _model->GetData()->StartDialogueID);
	}
}

void AUnitNPC::OnExitOverlap()
{
	GetMesh()->CustomDepthStencilValue = 0;
	GetMesh()->MarkRenderStateDirty();
}
