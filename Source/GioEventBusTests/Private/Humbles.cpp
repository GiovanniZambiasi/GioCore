// Copyright MiddleMast. All rights reserved

#include "Humbles.h"

void FHumbleRawListener::HandleHumbleEvent(const FHumbleEvent& Event)
{
	bHasReceivedEvent = true;
}

void UHumbleUObjectListener::HandleHumbleEvent(const FHumbleEvent& Event)
{
	bHasReceivedEvent = true;
}
