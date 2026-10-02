// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class project : ModuleRules
{
	public project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"project",
			"project/Variant_Platforming",
			"project/Variant_Platforming/Animation",
			"project/Variant_Combat",
			"project/Variant_Combat/AI",
			"project/Variant_Combat/Animation",
			"project/Variant_Combat/Gameplay",
			"project/Variant_Combat/Interfaces",
			"project/Variant_Combat/UI",
			"project/Variant_SideScrolling",
			"project/Variant_SideScrolling/AI",
			"project/Variant_SideScrolling/Gameplay",
			"project/Variant_SideScrolling/Interfaces",
			"project/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
