#include "Unit.h"
#include "EngineMinimal.h"
#include "RPGProject/Actor/DamageTextPooler.h"

AUnit::AUnit()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AUnit::BeginPlay()
{
	Super::BeginPlay();
	
}


void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

const bool AUnit::GetFalling()
{
	return GetCharacterMovement()->IsFalling();
}

const bool AUnit::GetAcceling()
{
	return !GetCharacterMovement()->GetCurrentAcceleration().IsZero();
}

const double AUnit::GetCurrentMoveSpeed()
{
	return GetCharacterMovement()->Velocity.Size2D();
}

void AUnit::displayDamage(int32 damage, FColor color)
{
	ADamageTextPooler* pooler = ADamageTextPooler::GetInstance();
	if (!pooler)
		return;

	ADamageActor* damageActor = pooler->GetPooledObject();
	if (!damageActor)
		return;

	damageActor->SetColor(color);
	damageActor->DisplayDamage(damage);
	damageActor->SetActorLocation(GetOwner()->GetActorLocation() + (FVector::UpVector * 5.0f));

}

void AUnit::Impulse(FVector dir)
{
	//무브먼트 컴포넌트를 밀어내면 될듯.
}

void AUnit::Damage(int32 damage)
{
	displayDamage(damage, FColor::Red);
}
