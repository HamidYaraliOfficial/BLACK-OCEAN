// BLACK OCEAN - Game Target
using UnrealBuildTool;
using System.Collections.Generic;

public class BlackOceanTarget : TargetRules
{
	public BlackOceanTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("BlackOcean");
	}
}
