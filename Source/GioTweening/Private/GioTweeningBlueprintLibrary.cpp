// Fill out your copyright notice in the Description page of Project Settings.


#include "GioTweeningBlueprintLibrary.h"

#include "GioTweening.h"
#include "GioTweeningService.h"

FGioTweenHandle UGioTweeningBlueprintLibrary::SetFloatTweenByEvent(float From, float To, FGioTweenSettings Settings,
                                                        FGioTweeningDynamicDelegate Callback)
{
	const auto* WorldContextObject = Callback.GetUObject();
	IGioTweeningService* TweeningService = IGioTweeningService::Get(WorldContextObject);

	if (TweeningService)
	{
		return TweeningService->SetTween(From, To, Settings, FGioTweeningDelegate::CreateWeakLambda(WorldContextObject,
			                          [=](float Alpha)
			                          {
				                          Callback.ExecuteIfBound(Alpha);
			                          }));
	}

	UE_LOG(LogGioTweening, Error, TEXT("Failed to start tween. Could not retrieve tweening subsystem from '%s'"),
	       *GetNameSafe(WorldContextObject))

	return FGioTweenHandle{};
}

FGioTweenHandle UGioTweeningBlueprintLibrary::SetVectorTweenByEvent(FVector From, FVector To, FGioTweenSettings Settings,
                                                         FGioTweeningVectorDelegate Callback)
{
	const auto* WorldContextObject = Callback.GetUObject();
	IGioTweeningService* TweeningService = IGioTweeningService::Get(WorldContextObject);

	if (TweeningService)
	{
		return TweeningService->SetTween(0.f, 1.f, Settings,
		                          FGioTweeningDelegate::CreateWeakLambda(WorldContextObject, [=](float Alpha)
		                          {
			                          FVector VectorAlpha = FMath::Lerp(From, To, Alpha);
			                          Callback.ExecuteIfBound(VectorAlpha);
		                          }));
	}
	
	UE_LOG(LogGioTweening, Error, TEXT("Failed to start tween. Could not retrieve tweening subsystem from '%s'"),
	       *GetNameSafe(WorldContextObject))

	return FGioTweenHandle{};
}

FGioTweenHandle UGioTweeningBlueprintLibrary::SetActorLocationTween(AActor* Actor, FVector To, FGioTweenSettings Settings,
                                                         bool bSweep, ETeleportType Teleport)
{
	if(!Actor)
	{
		UE_LOG(LogGioTweening, Error, TEXT("Failed to start tween. Actor is null"))
		return FGioTweenHandle{};
	}
	
	IGioTweeningService* TweeningService = IGioTweeningService::Get(Actor);

	if (TweeningService)
	{
		FVector From = Actor->GetActorLocation();
		TWeakObjectPtr<AActor> ActorWeak = Actor;
		return TweeningService->SetTween(0.f, 1.f, Settings,
		                          FGioTweeningDelegate::CreateWeakLambda(Actor, [=](float Alpha)
		                          {
			                          FVector VectorAlpha = FMath::Lerp(From, To, Alpha);
			                          if (ActorWeak.IsValid())
			                          {
				                          ActorWeak->SetActorLocation(VectorAlpha, bSweep, nullptr, Teleport);
			                          }
		                          }));
	}
	
	UE_LOG(LogGioTweening, Error, TEXT("Failed to start tween. Could not retrieve tweening subsystem from '%s'"),
	       *GetNameSafe(Actor))

	return FGioTweenHandle{};
}

bool UGioTweeningBlueprintLibrary::IsTweenActive(AActor* Context, const FGioTweenHandle& Handle)
{
	IGioTweeningService* TweeningService = IGioTweeningService::Get(Context);
	return TweeningService->IsTweenActive(Handle);
}

void UGioTweeningBlueprintLibrary::StopTweenAndClearHandle(AActor* Context, FGioTweenHandle& Handle)
{
	IGioTweeningService* TweeningService = IGioTweeningService::Get(Context);
	TweeningService->StopTweenAndClearHandle(Handle);
}
