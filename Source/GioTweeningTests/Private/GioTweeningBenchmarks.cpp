#include "GioCoreTests.h"
#include "GioTweeningService.h"
#include "GioTweeningTests.h"

BEGIN_DEFINE_SPEC(FGioTweeningBenchmarks, TEXT("GioTweeningBenchmarks"), EAutomationTestFlags::ApplicationContextMask
                  | EAutomationTestFlags::ProductFilter)

	IGioTweeningService* TweeningService{nullptr};
	UWorld* World{nullptr};

END_DEFINE_SPEC(FGioTweeningBenchmarks)

void FGioTweeningBenchmarks::Define()
{
	BeforeEach([this]
	{
		World = FGioTestUtils::OpenEmptyMap();
		TweeningService = IGioTweeningService::Get(World);
		check(TweeningService)
		GEngine->Exec(World, TEXT("stat startfile"));
	});

	It(TEXT("OneMillion_Identical_3Iterations"), [this]
	{
		FGioTweenSettings Settings{};
		Settings.Iterations = 3;
		Settings.Duration = 2.f;

		for (int i = 0; i < 1000000; ++i)
		{
			TweeningService->SetTween(0.f, 1.f, Settings, FGioTweeningDelegate::CreateLambda([](float)
			{
			}));
		}

		ADD_LATENT_AUTOMATION_COMMAND(FWaitForTweensToFinish{TweeningService});
	});

	It(TEXT("OneMillion_VaryingEasing_3Iterations"), [this]
	{
		FGioTweenSettings Settings{};
		Settings.Iterations = 3;
		Settings.Duration = 2.f;
		Settings.Easing = EEasingFunc::EaseInOut;

		for (int i = 0; i < 1000000; ++i)
		{
			TweeningService->SetTween(0.f, 1.f, Settings, FGioTweeningDelegate::CreateLambda([](float)
			{
			}));
		}

		ADD_LATENT_AUTOMATION_COMMAND(FWaitForTweensToFinish{TweeningService});
	});

	AfterEach([this]
	{
		ADD_LATENT_AUTOMATION_COMMAND(FUnloadMapAndFinishProfiling{World});
	});
}
