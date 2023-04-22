#include "GioTweeningTests.h"

#include "GioCoreTests.h"
#include "GioTweeningService.h"
#include "Tests/AutomationCommon.h"

IMPLEMENT_MODULE(FDefaultModuleImpl, GioTweeningTests)

bool FWaitForTweensToFinish::Update()
{
	UWorld* World = FGioTestUtils::GetFirstRunningMap();
	if(!World)
	{
		return false;
	}
	
	auto TweeningService = IGioTweeningService::Get(World);
	return TweeningService && TweeningService->GetActiveTweenCount() == 0;
}

bool FUnloadMapAndFinishProfiling::Update()
{
	UWorld* World = FGioTestUtils::GetFirstRunningMap();
	if(!World)
	{
		return true;
	}
	
	GEngine->Exec(World, TEXT("stat stopfile"));
	FGioTestUtils::CloseMap(World);
	return true;
}
