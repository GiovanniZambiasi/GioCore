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
		if (String == EaseInOut)
		{
			return EEasingFunc::EaseInOut;
		}
		if (String == EaseOut)
		{
			return EEasingFunc::EaseOut;
		}

		return EEasingFunc::Linear;
	}
}

IMPLEMENT_COMPLEX_AUTOMATION_TEST(FGioOneMillionIdenticalTweensBenchmark, TEXT("GioTweeningBenchmarks"),
                                  EAutomationTestFlags::ApplicationContextMask
                                  | EAutomationTestFlags::ProductFilter)

void FGioOneMillionIdenticalTweensBenchmark::GetTests(TArray<FString>& OutBeautifiedNames,
                                                      TArray<FString>& OutTestCommands) const
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
	ADD_LATENT_AUTOMATION_COMMAND(FGioOpenMapCommand(FGioTestUtils::EmptyMapPath));

	ADD_LATENT_AUTOMATION_COMMAND(FGioLatentAutomationCommandWrapper{FGioAutomationDelegate::CreateLambda([=]
	{
		auto WorldPtr = FGioTestUtils::TryGetRunningMap(FGioTestUtils::EmptyMapPath);
		auto TweeningService = IGioTweeningService::Get(WorldPtr);
		check(TweeningService)

		FString FileName{FString::Printf(TEXT("GioTweens/OneMillionIdentical_%s_%s"), *Parameters, *FDateTime::Now().
			ToString(TEXT("%Y-%m-%d_%H-%M-%S")))};
		GEngine->Exec(WorldPtr, *FString::Printf(TEXT("stat startfile %s"), *FileName));

		FGioTweenSettings Settings{};
		Settings.Iterations = 3;
		Settings.Duration = 2.f;
		Settings.Easing = FromString(Parameters);

		for (int i = 0; i < 1000000; ++i)
		{
		TweeningService->SetTween(0.f, 1.f, Settings,
			FGioTweeningDelegate::CreateLambda([](float){ }));
		}
		return true;
	})})

	ADD_LATENT_AUTOMATION_COMMAND(FWaitForTweensToFinish{});
	ADD_LATENT_AUTOMATION_COMMAND(FUnloadMapAndFinishProfiling{});

	return true;
}