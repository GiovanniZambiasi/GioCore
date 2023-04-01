// Copyright MiddleMast. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GioEvent.h"
#include "Components/ActorComponent.h"
#include "GioNetworkedEventBusComponent.generated.h"

class FGioEventBus;

/**
 * @brief Wrapper that implements generic struct serialization for FGioEvents
 */
USTRUCT()
struct FGioEventNetworkHelper
{
	GENERATED_BODY()

	FGioEventNetworkHelper() = default;

	FGioEventNetworkHelper(UScriptStruct* Struct, const FGioEvent* InEvent)
		: StructName(Struct->GetName()), Event(InEvent)
	{	}

	UPROPERTY(VisibleAnywhere)
	FString StructName{};

	const FGioEvent* Event { nullptr };

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	TOptional<UScriptStruct*> GetStruct() const;
};

template <>
struct TStructOpsTypeTraits<FGioEventNetworkHelper> : public TStructOpsTypeTraitsBase2<FGioEventNetworkHelper>
{
	enum
	{
		WithNetSerializer = true,
	};
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GIOEVENTBUS_API UGioNetworkedEventBusComponent : public UActorComponent
{
	GENERATED_BODY()

	TSharedPtr<FGioEventBus> Bus;

public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void SetBus(const TSharedPtr<FGioEventBus>& InBus);

	void ResetBus();

private:
	bool IsResponsibleForReplication() const { return GetOwner()->HasAuthority(); }
	
	void HandleEventDispatched(UScriptStruct* ScriptStruct, const FGioEvent& GioEvent);

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticastReplicateEvent(FGioEventNetworkHelper EventPayload);
};
