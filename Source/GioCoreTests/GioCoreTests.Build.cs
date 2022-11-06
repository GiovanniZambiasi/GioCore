// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GioCoreTests : ModuleRules
{
	public GioCoreTests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
			}
		);
		
		CppStandard = CppStandardVersion.Cpp17;
	}
}