#include "GioTween.h"

FGioTween::FGioTween(float InFrom, float InTo, const FGioTweenSettings& InSettings, FGioTweeningDelegate&& InCallback)
	: From(InFrom)
	  , To(InTo)
	  , RemainingIterations(InSettings.Iterations)
	  , Settings(InSettings)
	  , Callback(MoveTemp(InCallback))
{
}

void FGioTween::Tick(float DeltaTime)
{
	Time += DeltaTime;

	if (Time >= Settings.Duration)
	{
		HandleLoopComplete();
	}

	float Alpha = Time/Settings.Duration;
	Alpha = UKismetMathLibrary::Ease(From, To, bForward ? Alpha : 1 - Alpha, Settings.Easing);

	Callback.ExecuteIfBound(Alpha);
}

void FGioTween::HandleLoopComplete()
{
	--RemainingIterations;

	if (RemainingIterations == 0)
	{
		bComplete = true;
		Time = Settings.Duration;
	}
	else
	{
		Time -= Settings.Duration;

		if(Settings.LoopBehaviour == EGioTweeningLoopBehaviors::PingPong)
		{
			bForward = !bForward;
		}
	}
}
