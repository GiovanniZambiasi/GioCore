// Copyright MiddleMast. All rights reserved

#pragma once

#include "CoreMinimal.h"

class GIOCORETESTS_API FGioTestUtils
{
public:
	inline static FString const EmptyMapPath = TEXT("/GioCore/EmptyMap.EmptyMap'");
	
	static UWorld* GetFirstRunningMap();

	static UWorld* TryGetRunningMap(const FString& MapPath);
	
	static void CloseMap(UWorld* const World);

private:
	FGioTestUtils() = default;
};

using FGioAutomationDelegate = TDelegate<bool()>;

/**
 * @brief Opens a map and waits until it has begun play
 */
class GIOCORETESTS_API FGioOpenMapCommand : public IAutomationLatentCommand
{
public:
	FGioOpenMapCommand(const FString& InMapPath) : MapPath(InMapPath) { }

	virtual ~FGioOpenMapCommand() = default;

	virtual bool Update() override;
	
private:
	FString MapPath;
	
	bool bIsLoadingMap{false};
};

/**
 * @brief Wrapper for a latent automation command, taking in a lambda function. Useful to keep all the test logic
 * within the scope of "RunTest", so they read almost like a synchronous test.
 */
class GIOCORETESTS_API FGioLatentAutomationCommandWrapper : public IAutomationLatentCommand
{
public:
	FGioLatentAutomationCommandWrapper(FGioAutomationDelegate Callback)
		: Command(Callback)
	{ }

	virtual ~FGioLatentAutomationCommandWrapper()	{	}

	virtual bool Update() override;

private:
	FGioAutomationDelegate Command;
};

/**
 * @brief Shorthand for adding a FGioLatentAutomationCommandWrapper with a lambda function.
 * @param Lambda Standard lambda syntax starting with the captures block "[]" 
 */
#define ADD_GIO_LATENT_AUTOMATION_COMMAND_LAMBDA_WRAPPER(Lambda)\
	ADD_LATENT_AUTOMATION_COMMAND(FGioLatentAutomationCommandWrapper{FGioAutomationDelegate::CreateLambda(Lambda)})