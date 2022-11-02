// Copyright MiddleMast. All rights reserved

#include "GioEventBus.h"
#include "CoreMinimal.h"
#include "Humbles.h"

BEGIN_DEFINE_SPEC(FGioEventBusTests, "GioEventBus", EAutomationTestFlags::ApplicationContextMask
                  | EAutomationTestFlags::ProductFilter)

	FGioEventBus Bus;

END_DEFINE_SPEC(FGioEventBusTests)

void FGioEventBusTests::Define()
{
	BeforeEach([&]
	{
		Bus = FGioEventBus{};
	});

	It(TEXT("GivenNoListeners_WhenBroadcast_NoError"), [&]
	{
		Bus.Dispatch(FHumbleEvent{});
	});

	It(TEXT("GivenOneRawListener_WhenBroadcast_ListensToEvent"), [&]
	{
		FHumbleRawListener Listener{};

		Bus.RegisterListener<FHumbleEvent>(
			TGioEventDelegate<FHumbleEvent>::CreateRaw(&Listener, &FHumbleRawListener::HandleHumbleEvent));

		Bus.Dispatch(FHumbleEvent{});

		TestTrue(TEXT("Event is listened"), Listener.GetHasReceivedEvent());
	});

	It(TEXT("GivenMultipleRawListeners_WhenBroadcast_ListensToEvent"), [&]
	{
		TArray<FHumbleRawListener*> Listeners{};

		for (int i = 0; i < 5; ++i)
		{
			FHumbleRawListener Listener{};
			Bus.RegisterListener<FHumbleEvent>(
				TGioEventDelegate<FHumbleEvent>::CreateRaw(&Listener, &FHumbleRawListener::HandleHumbleEvent));
			Listeners.Add(&Listener);
		}

		Bus.Dispatch(FHumbleEvent{});

		int32 NumOfEventsListened = Listeners.FilterByPredicate([&](const FHumbleRawListener* Element)
		{
			return Element->GetHasReceivedEvent();
		}).Num();

		TestTrue(TEXT("All Listeners have received event"), NumOfEventsListened == Listeners.Num());
	});

	It(TEXT("GivenRegisteredListener_WhenUnregistered_DoesntReceiveBroadcast"), [&]
	{
		FHumbleRawListener Listener{};

		auto Handle = Bus.RegisterListener<FHumbleEvent>(
			TGioEventDelegate<FHumbleEvent>::CreateRaw(&Listener, &FHumbleRawListener::HandleHumbleEvent));

		Bus.UnregisterListener<FHumbleEvent>(Handle);

		Bus.Dispatch(FHumbleEvent{});

		TestFalse(TEXT("Broadcast not received"), Listener.GetHasReceivedEvent());
	});

	It(TEXT("GivenRegisteredListeners_WhenCleared_NoBroadcastsReceived"), [&]
	{
		FHumbleRawListener Listener{};

		auto Handle = Bus.RegisterListener<FHumbleEvent>(
			TGioEventDelegate<FHumbleEvent>::CreateRaw(&Listener, &FHumbleRawListener::HandleHumbleEvent));

		Bus.ClearListenersOfEvent<FHumbleEvent>();

		Bus.Dispatch(FHumbleEvent{});

		TestFalse(TEXT("Broadcast not received"), Listener.GetHasReceivedEvent());
	});

	It(TEXT("GivenOneRegisteredListener_WhenRemoveAll_NoBroadcastsReceived"), [&]
	{
		FHumbleRawListener Listener{};

		Bus.RegisterListener<FHumbleEvent>(
			TGioEventDelegate<FHumbleEvent>::CreateRaw(&Listener, &FHumbleRawListener::HandleHumbleEvent));

		Bus.RemoveAllListenersBoundToObject(&Listener);

		Bus.Dispatch(FHumbleEvent{});

		TestFalse(TEXT("Broadcast not received"), Listener.GetHasReceivedEvent());
	});

	It(TEXT("GiivenListenersA&B_WhenRemoveAllFromA_OnlyBroadcastsToB"), [&]
	{
		FHumbleRawListener ListenerA{};
		FHumbleRawListener ListenerB{};

		Bus.RegisterListener<FHumbleEvent>(
			TGioEventDelegate<FHumbleEvent>::CreateRaw(&ListenerA, &FHumbleRawListener::HandleHumbleEvent));
		Bus.RegisterListener<FHumbleEvent>(
			TGioEventDelegate<FHumbleEvent>::CreateRaw(&ListenerB, &FHumbleRawListener::HandleHumbleEvent));

		Bus.RemoveAllListenersBoundToObject(&ListenerA);

		Bus.Dispatch(FHumbleEvent{});

		TestTrue(TEXT("A doesn't receive broadcast, but B does"), !ListenerA.GetHasReceivedEvent() && ListenerB.GetHasReceivedEvent());
	});
}
