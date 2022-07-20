// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LowPolyShooting : ModuleRules
{
	public LowPolyShooting(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
