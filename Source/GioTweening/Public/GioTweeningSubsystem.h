// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GioTweeningService.h"
#include "GioTweeningSubsystem.generated.h"

class FGioTween;

DECLARE_DYNAMIC_DELEGATE_OneParam(FGioTweeningDynamicDelegate, float, Alpha);

UCLASS(BlueprintType)
class GIOTWEENING_API UGioTweeningSubsystem : public UTickableWorldSubsystem, public IGioTweeningService
{
	GENERATED_BODY()

	TArray<FGioTween> ActiveTweens{};
	
public:
	virtual void Tick(float DeltaTime) override;
	
	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(UGioTweeningSubsystem, STATGROUP_Tickables);
	}

	virtual void SetTween(float From, float To, float Duration, FGioTweeningDelegate Callback,
	                      EEasingFunc::Type Easing = EEasingFunc::Type::Linear) override;

	UFUNCTION(BlueprintCallable)
	void SetTweenByEvent(float From, float To, float Duration, FGioTweeningDynamicDelegate Callback,
		EEasingFunc::Type Easing = EEasingFunc::Type::Linear);
	
private:
	void TickActiveTweens(float DeltaTime);

	void RemoveCompletedTweens();
};
