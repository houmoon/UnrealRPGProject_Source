
#include "LegacyEffect_Base.h"


// Sets default values
ALegacyEffect_Base::ALegacyEffect_Base()
{
	m_PSComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Legecy Particle System Component"));
	m_PSComponent->SetupAttachment(m_rootComponent);

}

// Called when the game starts or when spawned
void ALegacyEffect_Base::BeginPlay()
{
	Super::BeginPlay();

	m_PSComponent->OnSystemFinished.AddDynamic(this, &ALegacyEffect_Base::OnFinished);
}

// Called every frame
void ALegacyEffect_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALegacyEffect_Base::SetEffect(UParticleSystem* cascadeParticle)
{
	m_PSComponent->SetTemplate(cascadeParticle);
}

void ALegacyEffect_Base::OnFinished(UParticleSystemComponent* _PSC)
{
	Destroy();
}
