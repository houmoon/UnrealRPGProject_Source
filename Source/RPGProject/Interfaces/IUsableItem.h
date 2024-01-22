#pragma once

#include "CoreMinimal.h"

class IUsableItem
{
	public:
	virtual void OnUse() {}
	virtual ~IUsableItem() {}
};