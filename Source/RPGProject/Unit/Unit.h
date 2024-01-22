#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Unit.generated.h"

class AObjectPooler;

UCLASS()
class RPGPROJECT_API AUnit : public ACharacter
{
	GENERATED_BODY()

public:

	public: //Getters
	const bool				GetFalling();
	const bool				GetAcceling();
	const double			GetCurrentMoveSpeed();
	virtual FVector			GetLocalMoveDir() { return FVector::Zero(); }

	public: //Delegates

	public: //Messeages
	void					Impulse(FVector dir);
	virtual void			Attack() {}
	UFUNCTION(BlueprintCallable)
	virtual void			Damage(int32 damage);
	UFUNCTION()
	virtual void			Death(const int32 ID) {}

	protected:
	virtual void			displayDamage(int32 damage, FColor color);
	virtual void BeginPlay() override;

	public:	
	AUnit();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};