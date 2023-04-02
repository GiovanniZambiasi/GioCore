#include "GioTween.h"

FGioTween::FGioTween(float InFrom, float InTo, float InDuration, FGioTweeningDelegate&& InCallback,
                     EEasingFunc::Type InEasing, int32 InIterations, EGioTweeningLoopBehaviors InLoopBehavior)
	: From(InFrom)
	  , To(InTo)
	  , Duration(InDuration)
	  , Callback(MoveTemp(InCallback))
	  , Easing(InEasing)
	  , Iterations(InIterations)
	  , LoopBehaviour(InLoopBehavior)
{
}

void FGioTween::Tick(float DeltaTime)
{
	if (bComplete)
	{
		return;
	}

	Time += DeltaTime;

	if (Time >= Duration)
	{
		HandleLoopComplete();
	}

	float Alpha = Time/Duration;
	Alpha = UKismetMathLibrary::Ease(From, To, bForward ? Alpha : 1 - Alpha, Easing);

	Callback.ExecuteIfBound(Alpha);
}

void FGioTween::HandleLoopComplete()
{
	--Iterations;

	if (Iterations == 0)
	{
		bComplete = true;
		Time = Duration;
	}
	else
	{
		Time -= Duration;

		if(LoopBehaviour == EGioTweeningLoopBehaviors::PingPong)
		{
			bForward = !bForward;
		}
	}
}
