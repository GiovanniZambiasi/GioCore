// Copyright MiddleMast. All rights reserved

#pragma once

/**
 * @brief A centralized event system that works based on event types. The main purpose of the event bus is to serve as
 * an abstraction layer between senders an listeners. This facilitates the exchange of data between distant systems.
 * <br><br>
 * <b>All events must be USTRUCT!</b>
 * <br><br>
 * Listeners can be registered for a particular type of event (a USTRUCT called FGameOverEvent, for example). Whenever
 * an event of that type is broadcast, all listeners bound to it will be executed.
 * <br><br>
 */
class FGioEventBus
{
	TMap<FString, TUniquePtr<TMulticastDelegateBase<FDefaultDelegateUserPolicy>>> Listeners{};

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
	FDelegateHandle RegisterListener(TDelegate<void(TEvent)> Listener)
	{
		UScriptStruct* StructType = TEvent::StaticStruct();
		const auto EventName = StructType->GetName();

		TMulticastDelegate<void(TEvent)>* Delegate;

		if (Listeners.Find(EventName))
		{
			Delegate = static_cast<TMulticastDelegate<void(TEvent)>*>(Listeners[EventName].Get());
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

		auto* Delegate = static_cast<TMulticastDelegate<void(TEvent)>*>(Listeners[EventName].Get());
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
		UScriptStruct* StructType = Event.StaticStruct();
		auto EventName = StructType->GetName();
		if (Listeners.Contains(StructType->GetName()))
		{
			auto* CastedDelegate = static_cast<TMulticastDelegate<void(TEvent)>*>(Listeners[EventName].Get());
			CastedDelegate->Broadcast(Event);
		}
	}

private:
	template <typename TEvent>
	TMulticastDelegate<void(TEvent)>* CreateDelegateForEvent(const FString& Key)
	{
		auto* Delegate = new TMulticastDelegate<void(TEvent)>();
		Listeners.Add(Key, TUniquePtr<TMulticastDelegateBase<FDefaultDelegateUserPolicy>>{Delegate});
		return Delegate;
	}
};
