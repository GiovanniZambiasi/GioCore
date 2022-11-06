// Copyright MiddleMast. All rights reserved

#pragma once

#include "CoreMinimal.h"

class GIOCORETESTS_API FGioTestUtils
{
public:
	static FString const EmptyMapPath;
	
	static UWorld* OpenMap(const FString& FullPath);

	static UWorld* OpenEmptyMap() { return OpenMap(EmptyMapPath); }

	static void CloseMap(UWorld* const World);
	
private:
	FGioTestUtils(){};
};
