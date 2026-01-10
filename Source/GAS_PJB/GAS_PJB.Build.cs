// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GAS_PJB : ModuleRules
{
	public GAS_PJB(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",

			// AI Modules
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			
			// UI Modules
			"UMG",
			"Slate",
			"SlateCore",

			// VFX Modules
            "Niagara",

			// GAS Modules
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"GAS_PJB"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
