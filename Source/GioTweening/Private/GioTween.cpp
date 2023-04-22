#include "GioTween.h"

FGioTween::FGioTween(float InFrom, float InTo, uint32 Serial, const FGioTweenSettings& InSettings, FGioTweeningDelegate&& InCallback)
	: From(InFrom)
	  , To(InTo)
	  , Serial(Serial)
	  , Settings(InSettings)
	  , Callback(MoveTemp(InCallback))
      , RemainingIterations(InSettings.Iterations)
{
}

void FGioTween::Tick(float DeltaTime)
{
	Time += DeltaTime;

	if (Time >= Settings.Duration)
	{
		HandleLoopComplete();
	}

	CalculateAndBroadcastAlpha();
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

void FGioTween::CalculateAndBroadcastAlpha()
{
	float Alpha = Time/Settings.Duration;
	Alpha = UKismetMathLibrary::Ease(From, To, bForward ? Alpha : 1 - Alpha, Settings.Easing);

	Callback.ExecuteIfBound(Alpha);
}
