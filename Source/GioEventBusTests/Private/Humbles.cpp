// Copyright MiddleMast. All rights reserved

#include "Humbles.h"

void FHumbleRawListener::HandleHumbleEvent(FHumbleEvent Event)
{
	bHasReceivedEvent = true;
}

void UHumbleUObjectListener::HandleHumbleEvent(FHumbleEvent Event)
{
	bHasReceivedEvent = true;
}
