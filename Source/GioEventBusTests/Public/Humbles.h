// Copyright MiddleMast. All rights reserved

#pragma once

#include "GioEvent.h"

#include "Humbles.generated.h"

USTRUCT()
struct FHumbleEvent : public FGioEvent
{
	GENERATED_BODY()
};

class FHumbleRawListener
{
	bool bHasReceivedEvent{false};
	
public:
	bool GetHasReceivedEvent() const { return bHasReceivedEvent; }
	
	void HandleHumbleEvent(const FHumbleEvent& Event);
};

UCLASS()
class UHumbleUObjectListener : public UObject
{
	GENERATED_BODY()

	bool bHasReceivedEvent{false};
	
public:
	void HandleHumbleEvent(const FHumbleEvent& Event);
};

USTRUCT()
struct FHumbleEventWithParameters : public FGioEvent
{
	GENERATED_BODY()

	FHumbleEventWithParameters() = default;

	FHumbleEventWithParameters(int32 InParam)
	: Param(InParam)
	{ }
	
	int32 Param{0};
};
