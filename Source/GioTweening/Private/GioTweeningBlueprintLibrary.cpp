// Fill out your copyright notice in the Description page of Project Settings.


#include "GioTweeningBlueprintLibrary.h"

#include "GioTweening.h"
#include "GioTweeningService.h"

void UGioTweeningBlueprintLibrary::SetFloatTweenByEvent(float From, float To, FGioTweenSettings Settings,
		FGioTweeningDynamicDelegate Callback)
{
	const auto* WorldContextObject = Callback.GetUObject();
	IGioTweeningService* TweeningService = IGioTweeningService::Get(WorldContextObject);

	if (TweeningService)
	{
		TweeningService->SetTween(From, To, Settings, FGioTweeningDelegate::CreateWeakLambda(WorldContextObject,
			                          [=](float Alpha)
			                          {
				                          Callback.ExecuteIfBound(Alpha);
			                          }));
	}
	else
	{
		UE_LOG(LogGioTweening, Error, TEXT("Failed to start tween. Could not retrieve tweening subsystem from '%s'"),
		       *GetNameSafe(WorldContextObject))
	}
}

void UGioTweeningBlueprintLibrary::SetVectorTweenByEvent(FVector From, FVector To, FGioTweenSettings Settings,
		FGioTweeningVectorDelegate Callback)
{
	const auto* WorldContextObject = Callback.GetUObject();
	IGioTweeningService* TweeningService = IGioTweeningService::Get(WorldContextObject);

	if (TweeningService)
	{
		TweeningService->SetTween(0.f, 1.f, Settings, FGioTweeningDelegate::CreateWeakLambda(WorldContextObject,
			                          [=](float Alpha)
			                          {
				                          FVector VectorAlpha = FMath::Lerp(From, To, Alpha);
				                          Callback.ExecuteIfBound(VectorAlpha);
			                          }));
	}
	else
	{
		UE_LOG(LogGioTweening, Error, TEXT("Failed to start tween. Could not retrieve tweening subsystem from '%s'"),
			   *GetNameSafe(WorldContextObject))
	}
}

void UGioTweeningBlueprintLibrary::SetActorLocationTween(FVector From, FVector To, FGioTweenSettings Settings)
{
}
