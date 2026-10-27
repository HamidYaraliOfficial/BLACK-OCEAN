// BLACK OCEAN - Primary Game Module
using UnrealBuildTool;

public class BlackOcean : ModuleRules
{
	public BlackOcean(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnableExceptions = true;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore",
			"EnhancedInput", "UMG", "Slate", "SlateCore",
			"Json", "JsonUtilities", "GameplayTags", "DeveloperSettings",
			"NetCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "RenderCore" });

		PublicIncludePaths.AddRange(new string[]
		{
			"BlackOcean/Core", "BlackOcean/Simulation", "BlackOcean/Ocean",
			"BlackOcean/Ships", "BlackOcean/Submarine", "BlackOcean/AirAssets",
			"BlackOcean/Crew", "BlackOcean/Sensors", "BlackOcean/Navigation",
			"BlackOcean/Fleet", "BlackOcean/Command", "BlackOcean/AI",
			"BlackOcean/Logistics", "BlackOcean/Ports", "BlackOcean/Shipyard",
			"BlackOcean/Research", "BlackOcean/Economy", "BlackOcean/Diplomacy",
			"BlackOcean/Missions", "BlackOcean/Dialogue", "BlackOcean/Save",
			"BlackOcean/Replay", "BlackOcean/UI", "BlackOcean/Networking",
			"BlackOcean/Tools"
		});
	}
}
