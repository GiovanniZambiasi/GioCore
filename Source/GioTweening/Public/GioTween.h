#pragma once
#include "GioTweeningService.h"
#include "GioTweeningUnifiedDelegate.h"

class FGioTween
{
public:
	FGioTween(float InFrom, float InTo, float InDuration, FGioTweeningUnifiedDelegate InCallback, EEasingFunc::Type InEasing);

	void Tick(float DeltaTime);
	
	bool IsComplete() const { return bComplete; }

private:
	float From{0.f};
	
	float To{0.f};
	
	float Duration{0.f};
	
	float Time{0.f};

	bool bComplete{false};

	FGioTweeningUnifiedDelegate Callback{};
	
	EEasingFunc::Type Easing{};
};
