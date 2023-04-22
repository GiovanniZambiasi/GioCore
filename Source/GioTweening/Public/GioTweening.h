#pragma once

#include "CoreMinimal.h"

class FGioTweeningModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

DECLARE_LOG_CATEGORY_EXTERN(LogGioTweening, Display, All)

DECLARE_STAT_GROUP(TEXT("Gio Tweening"), STATGROUP_GioTweening, STATCAT_Advanced, true, true, true)
