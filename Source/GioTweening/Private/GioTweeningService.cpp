#include "GioTweeningService.h"

#include "GioTweening.h"
#include "GioTweeningSubsystem.h"

IGioTweeningService* IGioTweeningService::Get(const UObject* WorldContextObject)
{
	checkf(WorldContextObject, TEXT("Tried to get tweening service with null context object"))
	UWorld* World = WorldContextObject->GetWorld();
	checkf(World, TEXT("Invalid WorldContextObj '%s' passed to tweening service"), *GetNameSafe(WorldContextObject))

	return World->GetSubsystem<UGioTweeningSubsystem>();
}

