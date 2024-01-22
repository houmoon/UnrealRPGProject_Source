// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Particles/ParticleSystemComponent.h"

#include "CoreMinimal.h"
#include "Effect_Base.h"
#include "LegacyEffect_Base.generated.h"


UCLASS()
class RPGPROJECT_API ALegacyEffect_Base : public AEffect_Base
{
	GENERATED_BODY()

	public:
	virtual void SetEffect(UParticleSystem* cascadeParticle) override;

	protected:
	//Legacy Particle System Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UParticleSystemComponent* m_PSComponent;


	protected:
	UFUNCTION()
	void OnFinished(UParticleSystemComponent* _PSC);


	public:
	ALegacyEffect_Base();
	protected:
	virtual void BeginPlay() override;
	public:
	virtual void Tick(float DeltaTime) override;
};
