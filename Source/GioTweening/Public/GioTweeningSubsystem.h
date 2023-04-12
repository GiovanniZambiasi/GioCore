// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GioTweeningService.h"
#include "GioTweeningSubsystem.generated.h"

class FGioTween;

UCLASS()
class UGioTweeningSubsystem : public UTickableWorldSubsystem, public IGioTweeningService
{
	GENERATED_BODY()

	TArray<FGioTween> ActiveTweens{};
	
public:
	virtual void Tick(float DeltaTime) override;
	
	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(UGioTweeningSubsystem, STATGROUP_Tickables);
	}

	virtual void SetTween(float From, float To, const FGioTweenSettings& Settings,
		FGioTweeningDelegate&& Callback) override;

	virtual int32 GetActiveTweenCount() const override { return ActiveTweens.Num(); }
	
private:
	void TickActiveTweens(float DeltaTime);

	void RemoveCompletedTweens();
};
