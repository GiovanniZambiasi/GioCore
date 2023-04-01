#include "GioTweening.h"

#define LOCTEXT_NAMESPACE "FGioTweeningModule"

void FGioTweeningModule::StartupModule()
{
}

void FGioTweeningModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FGioTweeningModule, GioTweening)

DEFINE_LOG_CATEGORY(LogGioTweening)