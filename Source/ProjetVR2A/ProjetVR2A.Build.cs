// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjetVR2A : ModuleRules
{
	public ProjetVR2A(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
