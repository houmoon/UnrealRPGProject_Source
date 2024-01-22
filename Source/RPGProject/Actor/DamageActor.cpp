#include "DamageActor.h"

#include "DamageTextPooler.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetTextLibrary.h"
#include "RPGProject/Global/Defines.h"
#include "RPGProject/UMG/WD_Text.h"

void ADamageActor::DisplayDamage(int32 damage)
{
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this]()
	{
		ReturnToPooler();

	}, 0.75f, false);

	_damageText->SetText(FText::AsNumber(damage));
	_damageText->PlayAnim();
}

void ADamageActor::SetParentPooler(ADamageTextPooler* pooler)
{
	_pooler = pooler;
}

void ADamageActor::ReturnToPooler()
{
	SetActorLocation(_pooler->GetActorLocation());
	IsEnabled = false;
}

void ADamageActor::SetColor(FColor color)
{
	_damageText->SetColorAndOpacity(FLinearColor::FromSRGBColor(color));
}

ADamageActor::ADamageActor()
{
	PrimaryActorTick.bCanEverTick = true;

	_widgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("widget Component"));
	_widgetComponent->SetupAttachment(RootComponent);
}

void ADamageActor::BeginPlay()
{
	Super::BeginPlay();

	_damageText = Cast<UWD_Text>(_widgetComponent->GetUserWidgetObject());
	
}

void ADamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}
