#pragma once
#include "GioTweeningService.h"
#include "GioTweeningSubsystem.h"

struct FGioTweeningUnifiedDelegate
{
	TOptional<FGioTweeningDelegate> Delegate{};
	
	TOptional<FGioTweeningDynamicDelegate> DynamicDelegate{};
	
	FGioTweeningUnifiedDelegate(FGioTweeningDelegate InDelegate)
		: Delegate(InDelegate)
	{  }
	
	FGioTweeningUnifiedDelegate(FGioTweeningDynamicDelegate InDelegate)
		: DynamicDelegate(InDelegate)
	{  }

	FGioTweeningUnifiedDelegate() = default;

	void Execute(float Alpha);
};
