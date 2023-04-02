#include "GioTweeningService.h"

#include "GioTweening.h"
#include "GioTweeningSubsystem.h"

IGioTweeningService* IGioTweeningService::Get(const UObject* WorldContextObject)
{
	UWorld* World = WorldContextObject->GetWorld();
	checkf(World, TEXT("Invalid WorldContextObj '%s' passed to tweening service"), *GetNameSafe(WorldContextObject))

	return World->GetSubsystem<UGioTweeningSubsystem>();
}

