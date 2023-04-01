// Copyright MiddleMast. All rights reserved

#include "GioGameEventsSubsystem.h"

void UGioGameEventsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	EventBus = MakeShared<FGioEventBus>();
}
