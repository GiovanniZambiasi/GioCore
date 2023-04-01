#pragma once
#include "Kismet/KismetMathLibrary.h"

DECLARE_DELEGATE_OneParam(FGioTweeningDelegate, float /*Alpha*/)

class GIOTWEENING_API IGioTweeningService
{
public:
	static IGioTweeningService* Get(const UObject* WorldContextObject);
	
	virtual ~IGioTweeningService() { }

	virtual void SetTween(float From, float To, float Duration, FGioTweeningDelegate Callback, EEasingFunc::Type Easing = EEasingFunc::Type::Linear) = 0;
};
