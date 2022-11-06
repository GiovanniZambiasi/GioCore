// Copyright MiddleMast. All rights reserved

#pragma once

#include "GioEventBus.h"
#include "GioGameEventsSubsystem.generated.h"

UCLASS()
class GIOEVENTBUS_API UGioGameEventsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	FGioEventBus EventBus;
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	FGioEventBus& GetEventBus() { return EventBus; }
};
