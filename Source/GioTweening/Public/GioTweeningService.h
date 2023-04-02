#pragma once
#include "Kismet/KismetMathLibrary.h"

DECLARE_DELEGATE_OneParam(FGioTweeningDelegate, float /*Alpha*/)

UENUM(BlueprintType)
enum class EGioTweeningLoopBehaviors : uint8
{
	Repeat,
	PingPong,
};

class GIOTWEENING_API IGioTweeningService
{
public:
	static IGioTweeningService* Get(const UObject* WorldContextObject);
	
	virtual ~IGioTweeningService() { }

	virtual void SetTween(float From, float To, float Duration, FGioTweeningDelegate&& Callback,
		EEasingFunc::Type Easing = EEasingFunc::Type::Linear, int32 Iterations = 1,
		EGioTweeningLoopBehaviors LoopBehavior = EGioTweeningLoopBehaviors::Repeat) = 0;
};
