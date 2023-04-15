// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GioTween.h"
#include "GioTweeningService.h"
#include "GioTweeningSubsystem.generated.h"

class FGioTween;

UCLASS()
class UGioTweeningSubsystem : public UTickableWorldSubsystem, public IGioTweeningService
{
	GENERATED_BODY()

	TArray<FGioTween> TweenPool{};

	TSet<uint32> ActiveTweenSerials{};

	uint32 LastAssignedTweenSerialNumber{0};
	
public:
	virtual void Tick(float DeltaTime) override;
	
	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(UGioTweeningSubsystem, STATGROUP_Tickables);
	}

	virtual FGioTweenHandle SetTween(float From, float To, const FGioTweenSettings& Settings,
		FGioTweeningDelegate&& Callback) override;

	virtual bool IsTweenActive(const FGioTweenHandle& Handle) const override;

	virtual uint32 GetActiveTweenCount() const override { return ActiveTweenSerials.Num(); }
	
	virtual void StopTweenAndClearHandle(FGioTweenHandle& Handle) override;

private:
	FGioTweenHandle RegisterTweenAndGetHandle(uint32 Index);

	uint32 FindIndexForNewTween();

	void TickActiveTweens(float DeltaTime);

	void ResetCompleteTweens();

	void StopTween(uint32 Index, uint32 Serial);
};
