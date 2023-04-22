// Copyright MiddleMast. All rights reserved

#include "GioCoreTests.h"

#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Tests/AutomationCommon.h"

IMPLEMENT_MODULE(FDefaultModuleImpl, GioCoreTests)

UWorld* FGioTestUtils::GetFirstRunningMap()
{
	if(!GEngine) return nullptr;

	TIndirectArray<FWorldContext> Contexts = GEngine->GetWorldContexts();

	for (FWorldContext& Context : Contexts)
	{
		if(Context.WorldType != EWorldType::PIE && Context.WorldType != EWorldType::Game || !Context.World())
			continue;
		
		auto World = Context.World();
		if(!World->AreActorsInitialized())
		{
			continue;	
		}

		auto GameState = World->GetGameState();
		if(GameState && GameState->HasMatchStarted())
		{
			return World;
		}
	}

	return nullptr;
}

UWorld* FGioTestUtils::TryGetRunningMap(const FString& MapPath)
{
	if(!GEngine) return nullptr;

	FString MapName = FPaths::GetBaseFilename(MapPath);

	TIndirectArray<FWorldContext> Contexts = GEngine->GetWorldContexts();

	for (FWorldContext& Context : Contexts)
	{
		if(Context.WorldType != EWorldType::PIE && Context.WorldType != EWorldType::Game || !Context.World())
			continue;

		UWorld* World = Context.World();
		if(World->GetName() != MapName || !World->AreActorsInitialized())
		{
			continue;	
		}

		auto GameState = World->GetGameState();
		if(GameState && GameState->HasMatchStarted())
		{
			return World;
		}
	}

	return nullptr;
}

void FGioTestUtils::CloseMap(UWorld* const World)
{
	if (APlayerController* TargetPC = UGameplayStatics::GetPlayerController(World, 0))
	{
		TargetPC->ConsoleCommand(TEXT("Exit"), true);
	}
}

bool FGioLatentAutomationCommandWrapper::Update()
{
	return Command.Execute();
}

bool FGioOpenMapCommand::Update()
{
	if(!bIsLoadingMap)
	{
		AutomationOpenMap(MapPath);
		bIsLoadingMap = true;
	}

	return FGioTestUtils::TryGetRunningMap(MapPath) != nullptr;
}

