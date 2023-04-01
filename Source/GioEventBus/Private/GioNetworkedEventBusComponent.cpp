// Copyright MiddleMast. All rights reserved

#include "GioNetworkedEventBusComponent.h"

#include "GioEventBus.h"

bool FGioEventNetworkHelper::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << StructName;

	TOptional<UScriptStruct*> Struct = GetStruct();

	if(!ensureMsgf(Struct, TEXT("Failed to find struct '%s'"), *StructName))
	{
		bOutSuccess = false;
		return false;
	}

	UScriptStruct* StructPtr = Struct.GetValue();
	
	if (Ar.IsSaving())
	{
		FGioEvent* EventWritable = const_cast<FGioEvent*>(Event);
		StructPtr->SerializeItem(Ar, EventWritable, nullptr);
	}

	if (Ar.IsLoading())
	{
		UScriptStruct::ICppStructOps* StructCppOps = StructPtr->GetCppStructOps();
		void* Allocation = FMemory::Malloc(StructPtr->GetStructureSize(), StructCppOps->GetAlignment());
		StructCppOps->Construct(Allocation);
		StructPtr->SerializeItem(Ar, Allocation, nullptr);
		Event = static_cast<FGioEvent*>(Allocation);
	}
		
	return true;
}

TOptional<UScriptStruct*> FGioEventNetworkHelper::GetStruct() const
{
	return FindObject<UScriptStruct>(ANY_PACKAGE, *StructName);
}

void UGioNetworkedEventBusComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ResetBus();
	Super::EndPlay(EndPlayReason);
}

void UGioNetworkedEventBusComponent::SetBus(const TSharedPtr<FGioEventBus>& InBus)
{
	ResetBus();
	Bus = InBus;
	
	if(Bus && IsResponsibleForReplication())
	{
		Bus->OnAnyEventDispatched().AddUObject(this, &ThisClass::HandleEventDispatched);
	}
}

void UGioNetworkedEventBusComponent::ResetBus()
{
	if(Bus)
	{
		Bus->OnAnyEventDispatched().RemoveAll(this);
		Bus.Reset();
	}
}

void UGioNetworkedEventBusComponent::HandleEventDispatched(UScriptStruct* ScriptStruct, const FGioEvent& GioEvent)
{
	if(!IsResponsibleForReplication())
	{
		return;
	}
	
	FGioEventNetworkHelper EventPayload{ScriptStruct, &GioEvent};
	NetMulticastReplicateEvent(EventPayload);
}

void UGioNetworkedEventBusComponent::NetMulticastReplicateEvent_Implementation(	FGioEventNetworkHelper EventPayload)
{
	if(IsResponsibleForReplication())
	{
		return;
	}
	
	if(Bus)
	{
		TOptional<UScriptStruct*> Struct = EventPayload.GetStruct();

		if(Struct)
		{
			Bus->Dispatch(Struct.GetValue(), *EventPayload.Event);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to find struct '%s'"), *EventPayload.StructName)
		}
	}
}