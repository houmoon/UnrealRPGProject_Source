// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Effect_Base.generated.h"


class UNiagaraSystem;

UCLASS()
class RPGPROJECT_API AEffect_Base : public AActor
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent* m_rootComponent;

	public:
	virtual void SetEffect(UParticleSystem* cascadeParticle) { }
	virtual void SetEffect(UNiagaraSystem* niagaraParticle) {}

public:	
	AEffect_Base();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

};
