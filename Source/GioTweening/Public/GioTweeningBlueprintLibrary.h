// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GioTweeningService.h"
#include "Kismet/KismetMathLibrary.h"
#include "GioTweeningBlueprintLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FGioTweeningDynamicDelegate, float, Alpha);

UCLASS()
class GIOTWEENING_API UGioTweeningBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Gio Tweening")
	static void SetFloatTweenByEvent(float From, float To, float Duration, FGioTweeningDynamicDelegate Callback,
		EEasingFunc::Type Easing = EEasingFunc::Type::Linear, int32 Iterations = 1,
		EGioTweeningLoopBehaviors LoopBehaviour = EGioTweeningLoopBehaviors::Repeat);
};
