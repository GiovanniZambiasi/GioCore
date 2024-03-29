﻿
#include "GioFunctionalTweeningBenchmark.h"

#include "GioTweeningService.h"


AGioFunctionalTweeningBenchmark::AGioFunctionalTweeningBenchmark()
{
	TimeLimit = 0.f;
}

void AGioFunctionalTweeningBenchmark::StartTest()
{
	Super::StartTest();

	auto* TweeningService = IGioTweeningService::Get(this);

	for (int i = 0; i < Instances; ++i)
	{
		TweeningService->SetTween(0.f, 1.f, Settings, FGioTweeningDelegate::CreateLambda([](float Alpha)
			{
			}));		
	}
}

void AGioFunctionalTweeningBenchmark::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto* TweeningService = IGioTweeningService::Get(this);
	GEngine->AddOnScreenDebugMessage(0, 0.f, FColor::Green, FString::Printf(TEXT("Active tweens %i"), TweeningService->GetActiveTweenCount()));

	if(TweeningService->GetActiveTweenCount() == 0)
	{
		
		FinishTest(EFunctionalTestResult::Succeeded, TEXT("Finished "));
	}
}
