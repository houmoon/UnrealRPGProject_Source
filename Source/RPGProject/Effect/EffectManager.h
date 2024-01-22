// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect_Structs.h"
#include "Effect_Base.h"

class UDAEffect;

class EffectManager
{
	public: static EffectManager* GetInstance();
	private: static EffectManager* _instance;

	public:
	void SetDataTable(class UDataTable* dataTable);

	private:
	//데이터 테이블
	class UDataTable* _dataTable;

	//검색을 위한 데이터
	TMap<EEFECT_TYPE, UNiagaraSystem*>	_niagaraDatas;


	public:
	EffectManager();

	void CreateEffect(EEFECT_TYPE type, ULevel* level, FVector location);

};
