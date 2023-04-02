
#include "GioTweeningBenchmark.h"

#include "GioTweeningService.h"


AGioTweeningBenchmark::AGioTweeningBenchmark()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGioTweeningBenchmark::BeginPlay()
{
	Super::BeginPlay();

	auto* TweeningService = IGioTweeningService::Get(this);

	for (int i = 0; i < Instances; ++i)
	{
		TweeningService->SetTween(0.f, 1.f, Duration, FGioTweeningDelegate::CreateLambda([](float Alpha)
			{
		
			}), Easing, Iterations, LoopBehaviour);		
	}
}
