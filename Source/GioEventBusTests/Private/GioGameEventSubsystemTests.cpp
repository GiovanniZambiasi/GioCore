// Copyright MiddleMast. All rights reserved

#include "Misc/AutomationTest.h"
#include "GioCoreTests.h"
#include "GioEvent.h"
#include "GioGameEventsSubsystem.h"

BEGIN_DEFINE_SPEC(FGameEventSubsystemTests, "GioGameEventSubsystemTests",
                  EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

	UWorld* World{nullptr};
	UGioGameEventsSubsystem* GameEventsSubsystem{nullptr};

END_DEFINE_SPEC(FGameEventSubsystemTests)

void FGameEventSubsystemTests::Define()
{
	BeforeEach([&]
	{
		ADD_LATENT_AUTOMATION_COMMAND(FGioOpenMapCommand{FGioTestUtils::EmptyMapPath})
		ADD_GIO_LATENT_AUTOMATION_COMMAND_LAMBDA_WRAPPER([&]
			{
			World = FGioTestUtils::TryGetRunningMap(FGioTestUtils::EmptyMapPath);
			check(World)
			GameEventsSubsystem = World->GetGameInstance()->GetSubsystem<UGioGameEventsSubsystem>();
			TestNotNull(TEXT("GameEventSubsystem not null"), GameEventsSubsystem);
			return true;
			})
	});

	AfterEach([&]
	{
		ADD_GIO_LATENT_AUTOMATION_COMMAND_LAMBDA_WRAPPER([&]
			{
			FGioTestUtils::CloseMap(World);
			World = nullptr;
			GameEventsSubsystem = nullptr;
			return true;
			})
	});

	It(TEXT("GivenGameEventSubsystem_WhenEventBroadcast_ListenersReceive"), [&]
	{
		ADD_GIO_LATENT_AUTOMATION_COMMAND_LAMBDA_WRAPPER([&]
			{
			auto Bus = GameEventsSubsystem->GetEventBus();
			bool bEventListened = false;

			Bus->RegisterListener<FGioEvent>(TGioEventDelegate<FGioEvent>::CreateLambda([&](const FGioEvent&)
				{
				bEventListened = true;
				}));

			Bus->Dispatch(FGioEvent{});

			TestTrue(TEXT("Event listened"), bEventListened);
			return true;
			})
	});
}
