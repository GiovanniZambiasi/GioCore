// Copyright MiddleMast. All rights reserved

#pragma once
#include "GioEvent.h"

struct FGioEvent;

DECLARE_EVENT_TwoParams(FGioEventBus, FGioEventDispatched, UScriptStruct* /*EventType*/, const FGioEvent& /*Event*/)

/**
 * @brief A centralized event system that works based on event types. The main purpose of the event bus is to serve as
 * an abstraction layer between senders an listeners. This facilitates the exchange of data between distant systems.
 * <br><br>
 * <b>All events must inherit from FGioEvent!</b>
 * <br><br>
 * Listeners can be registered for a particular type of event (a USTRUCT called FGameOverEvent, for example). Whenever
 * an event of that type is broadcast, all listeners bound to it will be executed.
 * <br><br>
 */
class FGioEventBus
{
	TMap<FString, TUniquePtr<TMulticastDelegateBase<FDefaultDelegateUserPolicy>>> Listeners{};

	FGioEventDispatched AnyEventDispatched{};
	
public:
	/**
	 * @brief Registers a method in the bus to be called whenever any events of type "TEvent" are broadcast.  
	 * @param Listener The delegate to be registered. Use one of the static methods from TGioEventDelegate<TEvent>
	 * to create the listener. Example:
	 * <br><br>
	 * TGioEventDelegate<FSomeEvent>::CreateLambda([](FSomeEvent Event){ Event Received Here! })
	 * <br><br>
	 * @return Delegate handle useful for unregistering the delegate later.
	 */
	template <typename TEvent>
	FDelegateHandle RegisterListener(TDelegate<void(const TEvent&)> Listener)
	{
		UScriptStruct* StructType = TEvent::StaticStruct();
		const auto EventName = StructType->GetName();

		TMulticastDelegate<void(const TEvent&)>* Delegate;

		if (Listeners.Find(EventName))
		{
			Delegate = static_cast<TMulticastDelegate<void(const TEvent&)>*>(Listeners[EventName].Get());
		}
		else
		{
			Delegate = CreateDelegateForEvent<TEvent>(EventName);
		}

		return Delegate->Add(Listener);
	}

	/**
	 * @brief Unregisters a listener for an event type. The FDelegateHandle is returned from the RegisterListener method
	 */
	template <typename TEvent>
	bool UnregisterListener(FDelegateHandle Handle)
	{
		UScriptStruct* StructType = TEvent::StaticStruct();
		const auto EventName = StructType->GetName();

		if (!Listeners.Contains(EventName))
		{
			return false;
		}

		auto* Delegate = static_cast<TMulticastDelegate<void(const TEvent&)>*>(Listeners[EventName].Get());
		return Delegate->Remove(Handle);
	}

	/**
	 * @brief Removes all registered listeners for a particular event type
	 */
	template <typename TEvent>
	void ClearListenersOfEvent()
	{
		UScriptStruct* StructType = TEvent::StaticStruct();
		const auto EventName = StructType->GetName();

		if (auto Delegate = Listeners.Find(EventName))
		{
			(*Delegate)->Clear();
		}
	}

	/**
	 * @brief Removes all listeners from all event types bound to a specific object
	 */
	int32 RemoveAllListenersBoundToObject(const void* UserObject)
	{
		int32 TotalRemovals{0};

		for (auto& Listener : Listeners)
		{
			TotalRemovals += Listener.Value->RemoveAll(UserObject);
		}

		return TotalRemovals;
	}

	/**
	 * @brief Broadcasts an event instance to all listeners of the event type.
	 */
	template <typename TEvent>
	void Dispatch(TEvent Event)
	{
		static_assert(std::is_base_of_v<FGioEvent, TEvent>, "Event must inherit from FGioEvent");
		UScriptStruct* StructType = Event.StaticStruct();
		Dispatch(StructType, Event);
	}

	void Dispatch(UScriptStruct* Type, const FGioEvent& Event)
	{
		auto EventName = Type->GetName();
		if (Listeners.Contains(Type->GetName()))
		{
			auto* CastedDelegate = static_cast<TMulticastDelegate<void(const FGioEvent&)>*>(Listeners[EventName].Get());
			CastedDelegate->Broadcast(Event);
		}

		if(AnyEventDispatched.IsBound())
		{
			AnyEventDispatched.Broadcast(Type, Event);
		}
	}

	FGioEventDispatched& OnAnyEventDispatched() { return AnyEventDispatched; }
	
private:
	template <typename TEvent>
	TMulticastDelegate<void(const TEvent&)>* CreateDelegateForEvent(const FString& Key)
	{
		auto* Delegate = new TMulticastDelegate<void(const TEvent&)>();
		Listeners.Add(Key, TUniquePtr<TMulticastDelegateBase<FDefaultDelegateUserPolicy>>{Delegate});
		return Delegate;
	}
};
