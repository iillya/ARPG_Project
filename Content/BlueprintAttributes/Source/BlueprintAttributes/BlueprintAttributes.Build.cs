// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

using UnrealBuildTool;

public class BlueprintAttributes : ModuleRules
{
	public BlueprintAttributes(ReadOnlyTargetRules Target) : base(Target)
	{
		// PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		ShortName = "GBARuntime";

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"GameplayAbilities",
				"NetCore",
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"GameplayTags",
				"Slate",
				"SlateCore",
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"BlueprintGraph",
					"EditorFramework",
					"RigVMDeveloper",
					"UnrealEd"
				}
			);
		}
		
		// TODO: Should this be setup ? as GameplayAbilities module is now doing
		// Without bUseIris to true in *.Target.cs file, this is a noop.
		// SetupIrisSupport(Target);
	}
}