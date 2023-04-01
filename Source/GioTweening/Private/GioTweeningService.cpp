#include "GioTweeningService.h"

#include "GioTweening.h"
#include "GioTweeningSubsystem.h"

IGioTweeningService* IGioTweeningService::Get(const UObject* WorldContextObject)
{
	UWorld* World = WorldContextObject->GetWorld();
	checkf(World, TEXT("Invalid WorldContextObj '%s' passed to tweening service"), *GetNameSafe(WorldContextObject))

	UGioTweeningSubsystem* Subsystem = World->GetSubsystem<UGioTweeningSubsystem>();
	if(!Subsystem)
	{
		UE_LOG(LogGioTweening, Error, TEXT("World '%s' doesn't have a tweening subsystem"), *GetNameSafe(World))
		return nullptr;
	}

	return Subsystem;
}

