#pragma once
#include "GioTweeningService.h"

class FGioTween
{
	float From{0.f};
	
	float To{0.f};
	
	float Time{0.f};

	int32 RemainingIterations{0};

	FGioTweenSettings Settings{};
	
	FGioTweeningDelegate Callback{};

	bool bComplete{false};

	bool bForward{true};
	
public:
	FGioTween(float InFrom, float InTo, const FGioTweenSettings& InSettings, FGioTweeningDelegate&& InCallback);

	void Tick(float DeltaTime);
	
	bool IsComplete() const { return bComplete; }

private:
	inline void HandleLoopComplete();
};
