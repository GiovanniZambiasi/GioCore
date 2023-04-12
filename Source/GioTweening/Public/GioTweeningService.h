#pragma once

#include "Kismet/KismetMathLibrary.h"
#include "GioTweeningService.generated.h"

DECLARE_DELEGATE_OneParam(FGioTweeningDelegate, float /*Alpha*/)

UENUM(BlueprintType)
enum class EGioTweeningLoopBehaviors : uint8
{
	Repeat,
	PingPong,
};

USTRUCT(BlueprintType)
struct GIOTWEENING_API FGioTweenSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EEasingFunc::Type> Easing{EEasingFunc::Type::Linear};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Iterations{1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGioTweeningLoopBehaviors LoopBehaviour{EGioTweeningLoopBehaviors::Repeat};
};

class GIOTWEENING_API IGioTweeningService
{
public:
	static IGioTweeningService* Get(const UObject* WorldContextObject);

	virtual ~IGioTweeningService() {  }
	
	virtual void SetTween(float From, float To, const FGioTweenSettings& Settings, FGioTweeningDelegate&& Callback) = 0;

	virtual int32 GetActiveTweenCount() const = 0;
};
