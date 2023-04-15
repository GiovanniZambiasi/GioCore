// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GioTweeningService.h"
#include "Kismet/KismetMathLibrary.h"
#include "GioTweeningBlueprintLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FGioTweeningDynamicDelegate, float, Alpha);

DECLARE_DYNAMIC_DELEGATE_OneParam(FGioTweeningVectorDelegate, FVector, Alpha);

UCLASS()
class GIOTWEENING_API UGioTweeningBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Gio Tweening")
	static void SetFloatTweenByEvent(float From, float To, FGioTweenSettings Settings,
		FGioTweeningDynamicDelegate Callback);

	UFUNCTION(BlueprintCallable, Category="Gio Tweening")
	static void SetVectorTweenByEvent(FVector From, FVector To, FGioTweenSettings Settings,
		FGioTweeningVectorDelegate Callback);

	UFUNCTION(BlueprintCallable, Category="Gio Tweening", Meta=(DefaultToSelf="Actor"))
	static void SetActorLocationTween(AActor* Actor, FVector To, FGioTweenSettings Settings, bool bSweep = false,
		ETeleportType Teleport = ETeleportType::None);
};
