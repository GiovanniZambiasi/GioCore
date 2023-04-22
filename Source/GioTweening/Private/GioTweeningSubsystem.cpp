// Fill out your copyright notice in the Description page of Project Settings.


#include "GioTweeningSubsystem.h"
#include "GioTween.h"

void UGioTweeningSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickActiveTweens(DeltaTime);
	ResetCompleteTweens();
}

FGioTweenHandle UGioTweeningSubsystem::SetTween(float From, float To, const FGioTweenSettings& Settings,
	FGioTweeningDelegate&& Callback)
{
	uint32 Index = FindIndexForNewTween();
	FGioTweenHandle Handle = RegisterTweenAndGetHandle(Index);
	TweenPool[Index] = FGioTween{From, To, Handle.Serial, Settings, MoveTemp(Callback)};
	return Handle;
}

bool UGioTweeningSubsystem::IsTweenActive(const FGioTweenHandle& Handle) const
{
	if(!ActiveTweenSerials.Contains(Handle.Serial) || !TweenPool.IsValidIndex(Handle.Index))
		return false;

	// A tween handle will be considered "active" if both its serial number matches with the active tween at the given
	// index. Technically it's possible for two different tween instances to have an identical handle, but the
	// likelihood of that happening is *very small*, since serial numbers only wrap around to 0 after about 4.2 billion
	return TweenPool[Handle.Index].GetSerial() == Handle.Serial;
}

void UGioTweeningSubsystem::StopTweenAndClearHandle(FGioTweenHandle& Handle)
{
	if(IsTweenActive(Handle))
	{
		StopTween(Handle.Index, Handle.Serial);
		Handle = FGioTweenHandle{};
	}
}

FGioTweenHandle UGioTweeningSubsystem::RegisterTweenAndGetHandle(uint32 Index)
{
	constexpr uint32 MaxIterations = ~0;

	for (int32 i = 0; i < MaxIterations; ++i)
	{
		uint32 Serial = ++LastAssignedTweenSerialNumber;

		if(Serial != 0 && !ActiveTweenSerials.Contains(Serial))
		{
			ActiveTweenSerials.Emplace(Serial);
			return FGioTweenHandle{Index, Serial};
		}
	}
	
	checkf(false, TEXT("No valid serial in 32 bit space for GioTween. Did you start tweens in a never-ending loop?"))
	return FGioTweenHandle{};
}

uint32 UGioTweeningSubsystem::FindIndexForNewTween()
{
	for (int i = LowestValidIndex; i < TweenPool.Num(); ++i)
	{
		if(!TweenPool[i].IsActive())
		{
			return i;
		}
	}

	++LowestValidIndex;
	return TweenPool.Emplace();
}

void UGioTweeningSubsystem::TickActiveTweens(float DeltaTime)
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("GioTweningSubsystem TickActiveTweens"), STAT_GioTweeningSubsystemTickActiveTweens, STATGROUP_GioTweening)
	for (FGioTween& Tween : TweenPool)
	{
		if(Tween.IsActive())
		{
			Tween.Tick(DeltaTime);
		}
	}
}

void UGioTweeningSubsystem::ResetCompleteTweens()
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("GioTweningSubsystem ResetCompleteTweens"), STAT_GioTweeningSubsystemResetCompleteTweens, STATGROUP_GioTweening)
	for (int i = 0; i < TweenPool.Num(); ++i)
	{
		FGioTween& Tween = TweenPool[i];
		
		if(Tween.IsComplete())
		{
			StopTween(i, Tween.GetSerial());
			Tween = FGioTween{};
		}
	}
}

void UGioTweeningSubsystem::StopTween(uint32 Index, uint32 Serial)
{
	check(TweenPool.IsValidIndex(Index))
	TweenPool[Index] = FGioTween{};
	ActiveTweenSerials.Remove(Serial);
	LowestValidIndex = Index;
}
