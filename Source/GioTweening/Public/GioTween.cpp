#include "GioTween.h"

FGioTween::FGioTween(float InFrom, float InTo, float InDuration, FGioTweeningUnifiedDelegate InCallback,
                     EEasingFunc::Type InEasing)
	: From(InFrom), To(InTo), Duration(InDuration), Callback(InCallback), Easing(InEasing)
{
}

void FGioTween::Tick(float DeltaTime)
{
	if(bComplete)
	{
		return;
	}
	
	Time += DeltaTime;

	if(Time >= Duration)
	{
		bComplete = true;
		Time = Duration;
	}
	
	float Alpha = UKismetMathLibrary::Ease(From, To, Time/Duration, Easing);
	
	if(Callback.Delegate)
	{
		Callback.Delegate.GetValue().ExecuteIfBound(Alpha);
	}
	else if(Callback.DynamicDelegate)
	{
		Callback.DynamicDelegate.GetValue().ExecuteIfBound(Alpha);
	}
}
