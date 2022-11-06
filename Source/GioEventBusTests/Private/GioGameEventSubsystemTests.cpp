// Copyright MiddleMast. All rights reserved

#include "Misc/AutomationTest.h"
#include "GioCoreTests.h"
#include "GioEvent.h"
#include "GioGameEventsSubsystem.h"

BEGIN_DEFINE_SPEC(FGameEventSubsystemTests, "GioGameEventSubsystemTests", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

UWorld* World{nullptr};
UGioGameEventsSubsystem* GameEventsSubsystem{nullptr};

END_DEFINE_SPEC(FGameEventSubsystemTests)

void FGameEventSubsystemTests::Define()
{
	BeforeEach([&]
	{
		World = FGioTestUtils::OpenEmptyMap();
		GameEventsSubsystem = World->GetGameInstance()->GetSubsystem<UGioGameEventsSubsystem>();
		TestNotNull(TEXT("GameEventSubsystem not null"), GameEventsSubsystem);
	});

	AfterEach([&]
	{
		FGioTestUtils::CloseMap(World);
		World = nullptr;
		GameEventsSubsystem = nullptr;
	});

	It(TEXT("GivenGameEventSubsystem_WhenEventBroadcast_ListenersReceive"), [&]
	{
		auto& Bus = GameEventsSubsystem->GetEventBus();
		bool bEventListened = false;
		
		Bus.RegisterListener<FGioEvent>(TGioEventDelegate<FGioEvent>::CreateLambda([&](FGioEvent)
		{
			bEventListened = true;
		}));

		Bus.Dispatch(FGioEvent{});

		TestTrue(TEXT("Event listened"), bEventListened);
	});
}
