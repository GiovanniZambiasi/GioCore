// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "GameFramework/Actor.h"
#include "GioTweeningService.h"
#include "GioFunctionalTweeningBenchmark.generated.h"

UCLASS()
class GIOTWEENINGTESTS_API AGioFunctionalTweeningBenchmark : public AFunctionalTest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Instances{10000};
	
	UPROPERTY(EditAnywhere)
	FGioTweenSettings Settings;

public:
	AGioFunctionalTweeningBenchmark();

protected:
	virtual void StartTest() override;

	virtual void Tick(float DeltaSeconds) override;
};
