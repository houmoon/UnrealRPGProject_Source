// Fill out your copyright notice in the Description page of Project Settings.

#include "EffectManager.h"

#include "LegacyEffect_Base.h"
#include "NiagaraEffect_Base.h"


#include "../Gamemode/Gamemode_Ingame.h"
#include "RPGProject/Global/Defines.h"

EffectManager* EffectManager::_instance = nullptr;

EffectManager::EffectManager()
{
}

EffectManager* EffectManager::GetInstance()
{
	if (nullptr == _instance)
	{
		_instance = new EffectManager();
	}

	return _instance;
}

void EffectManager::SetDataTable(UDataTable* dataTable)
{
	_dataTable = dataTable;

	FString str;
	TArray<FName> rowNames;

	rowNames = _dataTable->GetRowNames();

	 

	TArray<FEffectData*> arrTableData_eqp;
	_dataTable->GetAllRows<FEffectData>(str, arrTableData_eqp);
	for (int32 i = 0; i < arrTableData_eqp.Num(); i++)
	{
		_niagaraDatas.Add(arrTableData_eqp[i]->EffectType, arrTableData_eqp[i]->Asset);
	}

}

void EffectManager::CreateEffect(EEFECT_TYPE type, ULevel* level, FVector location)
{
	//Explode Effect 재생

	FActorSpawnParameters param = {};
	//바닥 충돌과 상관없이 무조건 스폰
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//현재 레벨로 스폰
	param.OverrideLevel = level;
	//바로 스폰하지 않고 대기
	param.bDeferConstruction = true;

	//FVector location = GetActorLocation() + GetActorForwardVector() * 100;
	FTransform transform;
	transform.SetLocation(location);

	AEffect_Base* pEffect;

	UNiagaraSystem** effect = _niagaraDatas.Find(type);

	if(!effect)
		return;


	pEffect = level->GetWorld()->SpawnActor<ANiagaraEffect_Base>(ANiagaraEffect_Base::StaticClass(), transform, param);

	if(effect)
	{
		pEffect->SetEffect(*effect);
		pEffect->FinishSpawning(pEffect->GetTransform()); //spawning을 종료하고 beginplay를 재생
	}
}
