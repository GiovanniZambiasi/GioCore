using UnrealBuildTool;

public class GioTweeningTests : ModuleRules
{
    public GioTweeningTests(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "GioTweening",
                "FunctionalTesting"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "GioCoreTests", "GioCoreTests"
            }
        );
    }
}