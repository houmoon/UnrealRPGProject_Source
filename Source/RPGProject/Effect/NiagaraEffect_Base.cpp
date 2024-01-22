// Fill out your copyright notice in the Description page of Project Settings.

#include "NiagaraEffect_Base.h"
#include "NiagaraComponent.h"


ANiagaraEffect_Base::ANiagaraEffect_Base()
{
	m_NIComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Particle System Component"));
	m_NIComponent->SetupAttachment(m_rootComponent);
}

void ANiagaraEffect_Base::BeginPlay()
{
	OnFinishedDelegate.BindUFunction(this, FName("OnFinished"));
	m_NIComponent->OnSystemFinished.Add(OnFinishedDelegate);
}

void ANiagaraEffect_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(m_NIComponent->GetAsset() && m_NIComponent->IsComplete())
		Destroy();

}

void ANiagaraEffect_Base::SetEffect(UNiagaraSystem* niagaraParticle)
{
	m_NIComponent->SetAsset(niagaraParticle);
}

void ANiagaraEffect_Base::OnFinished(UNiagaraComponent* _NIC)
{
	Destroy();
}
