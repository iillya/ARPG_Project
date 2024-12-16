// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

using UnrealBuildTool;

public class BlueprintAttributesDeveloper : ModuleRules
{
	public BlueprintAttributesDeveloper(ReadOnlyTargetRules Target) : base(Target)
	{
		ShortName = "GBADeveloper";

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"BlueprintGraph",
				"CoreUObject",
				"Engine",
				"GameplayAbilities",
				"BlueprintAttributes",
				"BlueprintAttributesEditor",
				"Projects",
				"Slate",
				"SlateCore",
			}
		);

		if (Target.bBuildEditor == true)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"UnrealEd",
				}
			);
		}
	}
}