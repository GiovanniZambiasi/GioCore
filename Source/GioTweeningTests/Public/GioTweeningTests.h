#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IGioTweeningService;

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FWaitForTweensToFinish, IGioTweeningService*, TweeningService);

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FUnloadMapAndFinishProfiling, UWorld*, Map);
