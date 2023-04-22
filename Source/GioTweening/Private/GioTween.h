#pragma once
#include "GioTweeningService.h"

class FGioTween
{
	float From{0.f};
	
	float To{0.f};

	uint32 Serial{0};

	FGioTweenSettings Settings{};
	
	FGioTweeningDelegate Callback{};

	float Time{0.f};
	
	int32 RemainingIterations{0};

	bool bComplete{false};

	bool bForward{true};
	
public:
	FGioTween(float InFrom, float InTo, uint32 Serial, const FGioTweenSettings& InSettings, FGioTweeningDelegate&& InCallback);

	FGioTween() = default;

	void Tick(float DeltaTime);

	bool IsComplete() const { return bComplete; }

	bool IsActive() const { return Serial != 0; }

	uint32 GetSerial() const { return Serial; }

private:
	inline void HandleLoopComplete();

	inline void CalculateAndBroadcastAlpha();
};
