// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "GioTweeningService.h"
#include "GioTweeningBenchmark.generated.h"

UCLASS()
class GIOTWEENINGTESTS_API AGioTweeningBenchmark : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Instances{10000};
	
	UPROPERTY(EditAnywhere)
	int32 Iterations{10};

	UPROPERTY(EditAnywhere)
	float Duration{1.f};

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEasingFunc::Type> Easing{};

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EGioTweeningLoopBehaviors> LoopBehaviour{};
	
public:
	AGioTweeningBenchmark();

protected:
	virtual void BeginPlay() override;
};
