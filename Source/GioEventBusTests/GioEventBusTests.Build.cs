// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GioEventBusTests : ModuleRules
{
	public GioEventBusTests(ReadOnlyTargetRules Target) : base(Target)
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
				"GioEventBus",
			}
		);
		
		CppStandard = CppStandardVersion.Cpp17;
	}
}