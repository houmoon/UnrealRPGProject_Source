


#include "AreaActor.h"

#include "Components/BoxComponent.h"
#include "RPGProject/Quest/QuestManager.h"

void AAreaActor::onOverlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Log,TEXT("Overlapped"));
	QuestManager::GetInstance()->OnMsgReceived(EQUEST_CLEAR_TYPE::APPROACHAREA, FCString::Atoi(*_rowName.RowName.ToString()));
}

// Sets default values
AAreaActor::AAreaActor()
{
	_boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"),false);

	_boxComp->OnComponentBeginOverlap.AddDynamic(this,&AAreaActor::onOverlapped);
}

