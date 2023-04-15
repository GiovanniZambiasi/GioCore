#include "GioCoreTests.h"
#include "GioTweeningService.h"
#include "GioTweeningTests.h"

namespace 
{
	const FString Linear{TEXT("Linear")};
	const FString EaseInOut{TEXT("EaseInOut")};
	const FString EaseOut{TEXT("EaseOut")};

	EEasingFunc::Type FromString(const FString& String)
	{
		if(String == EaseInOut)
		{
			return EEasingFunc::EaseInOut;
		}
		if(String == EaseOut)
		{
			return EEasingFunc::EaseOut;
		}

		return EEasingFunc::Linear;
	}
}

IMPLEMENT_COMPLEX_AUTOMATION_TEST(FGioOneMillionIdenticalTweensBenchmark, TEXT("GioTweeningBenchmarks"), EAutomationTestFlags::ApplicationContextMask
                                  | EAutomationTestFlags::ProductFilter)

void FGioOneMillionIdenticalTweensBenchmark::GetTests(TArray<FString>& OutBeautifiedNames, TArray<FString>& OutTestCommands) const
{
	OutBeautifiedNames.Append(
		{
			TEXT("OneMillion_Identical_Linear_3Iterations"),
			TEXT("OneMillion_Identical_EaseInOut_3Iterations"),
			TEXT("OneMillion_Identical_EaseOut_3Iterations"),
	});

	OutTestCommands.Append(
	{
		Linear,
		EaseInOut,
		EaseOut,
	});
}

bool FGioOneMillionIdenticalTweensBenchmark::RunTest(const FString& Parameters)
{
	auto World = FGioTestUtils::OpenEmptyMap();
	auto TweeningService = IGioTweeningService::Get(World);
	check(TweeningService)
	
	FString FileName{FString::Printf(TEXT("GioTweens/OneMillionIdentical_%s_%s"), *Parameters, *FDateTime::Now().ToString(TEXT("%Y-%m-%d_%H-%M-%S")))};
	GEngine->Exec(World, *FString::Printf(TEXT("stat startfile %s"), *FileName));

	FGioTweenSettings Settings{};
	Settings.Iterations = 3;
	Settings.Duration = 2.f;
	Settings.Easing = FromString(Parameters);

	for (int i = 0; i < 1000000; ++i)
	{
		TweeningService->SetTween(0.f, 1.f, Settings,
			FGioTweeningDelegate::CreateLambda([](float){ }));
	}

	ADD_LATENT_AUTOMATION_COMMAND(FWaitForTweensToFinish{TweeningService});
	ADD_LATENT_AUTOMATION_COMMAND(FUnloadMapAndFinishProfiling{World});

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGioOneMillionAlternatingTweensBenchmark, TEXT("GioTweeningBenchmarks.OneMillionAlternating"), EAutomationTestFlags::ApplicationContextMask
								  | EAutomationTestFlags::ProductFilter)

bool FGioOneMillionAlternatingTweensBenchmark::RunTest(const FString& Parameters)
{
	auto World = FGioTestUtils::OpenEmptyMap();
	auto TweeningService = IGioTweeningService::Get(World);
	check(TweeningService)
	
	FString FileName{FString::Printf(TEXT("GioTweens/OneMillionAlternating_%s"), *FDateTime::Now().ToString(TEXT("%Y-%m-%d_%H-%M-%S")))};
	GEngine->Exec(World, *FString::Printf(TEXT("stat startfile %s"), *FileName));

	FGioTweenSettings Settings{};
	Settings.Iterations = 3;
	Settings.Duration = 2.f;

	for (int i = 0; i < 1000000; ++i)
	{
		Settings.Easing = i % 2 == 0 ? EEasingFunc::EaseIn : EEasingFunc::EaseOut;
		
		TweeningService->SetTween(0.f, 1.f, Settings,
			FGioTweeningDelegate::CreateLambda([](float){ }));
	}

	ADD_LATENT_AUTOMATION_COMMAND(FWaitForTweensToFinish{TweeningService});
	ADD_LATENT_AUTOMATION_COMMAND(FUnloadMapAndFinishProfiling{World});

	return true;
}

