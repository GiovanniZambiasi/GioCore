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

USTRUCT(BlueprintType)
struct GIOTWEENING_API FGioTweenHandle
{
	GENERATED_BODY()

	FGioTweenHandle() = default;

	FGioTweenHandle(uint32 InIndex, uint32 InSerial)
		: Index(InIndex), Serial(InSerial)
	{
	}
	
	UPROPERTY(Transient)
	uint32 Index{0};

	UPROPERTY(Transient)
	uint32 Serial{0};

	/**
	 * @brief Checks if this handle has ever pointed to a valid tween instance. This <b>does not mean</b> the tween is
	 * currently active. For that check, use <i>IGioTweeningService's IsTweenActive</i> 
	 */
	bool IsValid() const { return Serial != 0; }
};

class GIOTWEENING_API IGioTweeningService
{
public:
	static IGioTweeningService* Get(const UObject* WorldContextObject);

	virtual ~IGioTweeningService() {  }
	
	virtual FGioTweenHandle SetTween(float From, float To, const FGioTweenSettings& Settings,
		FGioTweeningDelegate&& Callback) = 0;

	virtual uint32 GetActiveTweenCount() const = 0;

	/**
	 * @brief Checks if the tween handle is valid, and points to a currently active tween instance. This will return
	 * false after the tween has completed.
	 */
	virtual bool IsTweenActive(const FGioTweenHandle& Handle) const = 0;
	
	/**
	 * @brief Stops a tween and clears its handle
	 */
	virtual void StopTweenAndClearHandle(FGioTweenHandle& Handle) = 0;

};
