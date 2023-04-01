// Fill out your copyright notice in the Description page of Project Settings.


#include "GioTweeningSubsystem.h"

#include "GioTween.h"

void UGioTweeningSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickActiveTweens(DeltaTime);
	RemoveCompletedTweens();
}

void UGioTweeningSubsystem::SetTween(float From, float To, float Duration, FGioTweeningDelegate Callback,
                                     EEasingFunc::Type Easing)
{
	ActiveTweens.Emplace(From, To, Duration, Callback, Easing);
}

void UGioTweeningSubsystem::SetTweenByEvent(float From, float To, float Duration, FGioTweeningDynamicDelegate Callback,
	EEasingFunc::Type Easing)
{
	ActiveTweens.Emplace(From, To, Duration, Callback, Easing);
}

void UGioTweeningSubsystem::TickActiveTweens(float DeltaTime)
{
	for (FGioTween& Tween : ActiveTweens)
	{
		Tween.Tick(DeltaTime);
	}
}

void UGioTweeningSubsystem::RemoveCompletedTweens()
{
	for (int i = ActiveTweens.Num() - 1; i >= 0; --i)
	{
		if(ActiveTweens[i].IsComplete())
		{
			ActiveTweens.RemoveAt(i);
		}
	}
}
