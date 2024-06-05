#include "GioCoreTests.h"
#include "GioTweeningService.h"

BEGIN_DEFINE_SPEC(FGioTweeningServiceTests, TEXT("GioTweening"), EAutomationTestFlags::ApplicationContextMask
                  | EAutomationTestFlags::ProductFilter)

	IGioTweeningService* TweeningService{nullptr};
	UWorld* World{nullptr};

END_DEFINE_SPEC(FGioTweeningServiceTests)

void FGioTweeningServiceTests::Define()
{
	BeforeEach([&]
	{
		ADD_LATENT_AUTOMATION_COMMAND(FGioOpenMapCommand{FGioTestUtils::EmptyMapPath})
		ADD_GIO_LATENT_AUTOMATION_COMMAND_LAMBDA_WRAPPER([&]
			{
			UE_LOG(LogTemp, Display, TEXT("Before each being called!"))
			World = FGioTestUtils::TryGetRunningMap(FGioTestUtils::EmptyMapPath);
			check(World)
			TweeningService = IGioTweeningService::Get(World);
			check(TweeningService)
			UE_LOG(LogTemp, Display, TEXT("Latent command executing!"))
			return true;
			})
	});

	It(TEXT(""), [&]
	{
		ADD_GIO_LATENT_AUTOMATION_COMMAND_LAMBDA_WRAPPER([&]
		{
			UE_LOG(LogTemp, Display, TEXT("It being called!"))
			return true;
		})
	});

	AfterEach([&]
	{
		ADD_GIO_LATENT_AUTOMATION_COMMAND_LAMBDA_WRAPPER([&]
		{
			UE_LOG(LogTemp, Display, TEXT("After each being called!"))
			if(World)
			{
				FGioTestUtils::CloseMap(World);
				World = nullptr;
			}
			return true;
		})
	});
}
