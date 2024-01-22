// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect_Base.h"
#include "NiagaraEffect_Base.generated.h"


UCLASS()
class RPGPROJECT_API ANiagaraEffect_Base : public AEffect_Base
{
	GENERATED_BODY()

	public:
	virtual void SetEffect(UNiagaraSystem* niagaraParticle) override;

	protected:
	//Niagara Particle System Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UNiagaraComponent* m_NIComponent;


	protected:
	UFUNCTION()
	void OnFinished(UNiagaraComponent* _NIC);
	FScriptDelegate OnFinishedDelegate;

	public:
	ANiagaraEffect_Base();
	protected:
	virtual void BeginPlay() override;
	public:
	virtual void Tick(float DeltaTime) override;
};
