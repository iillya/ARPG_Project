// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

using UnrealBuildTool;

public class BlueprintAttributesScaffold : ModuleRules
{
	public BlueprintAttributesScaffold(ReadOnlyTargetRules Target) : base(Target)
	{
		// PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		ShortName = "GBAScaffold";
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"AppFramework",
				"ApplicationCore",
				"AssetTools",
				"BlueprintAttributes",
				"BlueprintAttributesEditorCommon",
				"BlueprintGraph",
				"CoreUObject",
				"DeveloperSettings",
				"DesktopPlatform",
				"Engine",
				"EngineSettings",
				"GameplayAbilities",
				"GameProjectGeneration",
				"MainFrame",
				"InputCore",
				"Projects",
				"Slate",
				"SlateCore",
				"ToolMenus",
				"ToolWidgets",
				"UnrealEd",
				"WorkspaceMenuStructure",
			}
		);
		
		if (Target.bWithLiveCoding)
		{
			PrivateIncludePathModuleNames.Add("LiveCoding");
		}
	}
}