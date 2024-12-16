// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class BlueprintAttributesEditor : ModuleRules
{
	public BlueprintAttributesEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		// PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		ShortName = "GBAEditor";
		
		var EngineDir = Path.GetFullPath(Target.RelativeEnginePath);

		// NOTE: General rule is not to access the private folder of another module,
		// but to use SPathPicker (used in SGBANewDataTableWindowContent), we need to include some private headers
		PrivateIncludePaths.AddRange(
			new string[]
			{
				// For access to SPathPicker (used in SGBANewDataTableWindowContent)
				Path.Combine(EngineDir, @"Source/Editor/ContentBrowser/Private")
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"AssetTools",
				"BlueprintAttributes",
				"Core",
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"BlueprintAttributesEditorCommon",
				"BlueprintAttributesScaffold",
				"BlueprintGraph",
				"ContentBrowserData",
				"CoreUObject",
				"DataTableEditor",
				"DeveloperSettings",
				"EditorFramework",
				"EditorSubsystem",
				"Engine",
				"GameplayAbilities",
				"GameplayTags",
				"GraphEditor",
				"InputCore",
				"Kismet",
				"KismetWidgets",
				"MessageLog",
				"RigVMDeveloper",
				"Slate",
				"SlateCore",
				"ToolWidgets",
				"UnrealEd",
			}
		);
	}
}
