#include "GioTweeningTests.h"

#include "GioCoreTests.h"
#include "GioTweeningService.h"

IMPLEMENT_MODULE(FDefaultModuleImpl, GioTweeningTests)

bool FWaitForTweensToFinish::Update()
{
	return TweeningService && TweeningService->GetActiveTweenCount() == 0;
}

bool FUnloadMapAndFinishProfiling::Update()
{
	GEngine->Exec(Map, TEXT("stat stopfile"));
	FGioTestUtils::CloseMap(Map);
	return true;
}
