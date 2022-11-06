// Copyright MiddleMast. All rights reserved

#include "GioCoreTests.h"

#include "Kismet/GameplayStatics.h"
#include "Tests/AutomationCommon.h"

IMPLEMENT_MODULE(FDefaultModuleImpl, GioCoreTests)

FString const FGioTestUtils::EmptyMapPath = TEXT("/GioCore/EmptyMap.EmptyMap'");

UWorld* FGioTestUtils::OpenMap(const FString& FullPath)
{
	checkf(AutomationOpenMap(FullPath), TEXT("Map not found @ path '%s'"), *FullPath);

	const auto MapName = FPaths::GetBaseFilename(FullPath);

	auto WorldContexts = GEngine->GetWorldContexts();

	for (auto WorldContext : GEngine->GetWorldContexts())
	{
		auto* World = WorldContext.World();

		if ((WorldContext.WorldType == EWorldType::PIE || WorldContext.WorldType == EWorldType::Game) && World &&
			World->GetName() == MapName)
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
