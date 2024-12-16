// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

using UnrealBuildTool;

public class BlueprintAttributesEditorCommon : ModuleRules
{
	public BlueprintAttributesEditorCommon(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		ShortName = "GBAEditorCommon";

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"EditorStyle",
				"Engine",
				"GameplayAbilities",
				"Projects",
				"Slate",
				"SlateCore",
			}
		);
	}
}