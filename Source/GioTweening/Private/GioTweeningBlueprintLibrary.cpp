// Fill out your copyright notice in the Description page of Project Settings.


#include "GioTweeningBlueprintLibrary.h"

#include "GioTweening.h"
#include "GioTweeningService.h"

void UGioTweeningBlueprintLibrary::SetFloatTweenByEvent(float From, float To, float Duration,
                                                        FGioTweeningDynamicDelegate Callback, EEasingFunc::Type Easing,
                                                        int32 Iterations, EGioTweeningLoopBehaviors LoopBehaviour)
{
	const auto* WorldContextObject = Callback.GetUObject();
	IGioTweeningService* TweeningService = IGioTweeningService::Get(WorldContextObject);

	if (TweeningService)
	{
		TweeningService->SetTween(From, To, Duration, FGioTweeningDelegate::CreateWeakLambda(WorldContextObject,
			                          [=](float Alpha)
			                          {
				                          Callback.ExecuteIfBound(Alpha);
			                          }), Easing, Iterations, LoopBehaviour);
	}
	else
	{
		UE_LOG(LogGioTweening, Error, TEXT("Failed to start tween. Could not retrieve tweening subsystem from '%s'"),
		       *GetNameSafe(WorldContextObject))
	}
}
