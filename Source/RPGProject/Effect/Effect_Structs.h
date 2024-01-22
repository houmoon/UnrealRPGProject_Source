#pragma once

#include <Engine/DataTable.h>

#include "Particles/ParticleSystem.h"
#include "NiagaraComponent.h"

#include "Effect_Structs.generated.h"


UENUM()
enum class EDECAL_TYPE : uint8
{
	CRASH = 1,
	NONE = 0
};

UENUM()
enum class EEFECT_TYPE : uint8 //uint8을 베이스로 자료형을 만듬.
{
	HIT_PUNCH_0,
	HIT_PUNCH_1,
	HIT_SWORD,
	HIT_ARROW,
	NONE,
};

UENUM()
enum class EEFECTCLASS_TYPE : uint8 //uint8을 베이스로 자료형을 만듬.
{
	CASCADE = 1,
	NIAGARA = 2,
	NONE = 0
};


USTRUCT(Atomic, BlueprintType)
struct FEffectData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EEFECT_TYPE	EffectType;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* Asset;

};