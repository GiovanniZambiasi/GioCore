#pragma once
#include "GioTweeningService.h"

class FGioTween
{
	float From{0.f};
	
	float To{0.f};
	
	float Duration{0.f};
	
	float Time{0.f};

	FGioTweeningDelegate Callback{};
	
	EEasingFunc::Type Easing{};

	int32 Iterations{1};
	
	EGioTweeningLoopBehaviors LoopBehaviour{EGioTweeningLoopBehaviors::Repeat};

	bool bComplete{false};

	bool bForward{true};
	
public:
	FGioTween(float InFrom, float InTo, float InDuration, FGioTweeningDelegate&& InCallback,
		EEasingFunc::Type InEasing, int32 InIterations, EGioTweeningLoopBehaviors InLoopBehavior);

	void Tick(float DeltaTime);
	
	bool IsComplete() const { return bComplete; }

private:
	inline void HandleLoopComplete();
};
