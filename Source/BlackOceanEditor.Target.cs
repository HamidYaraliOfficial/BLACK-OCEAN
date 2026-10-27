// BLACK OCEAN - Editor Target
using UnrealBuildTool;
using System.Collections.Generic;

public class BlackOceanEditorTarget : TargetRules
{
	public BlackOceanEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("BlackOcean");
	}
}
