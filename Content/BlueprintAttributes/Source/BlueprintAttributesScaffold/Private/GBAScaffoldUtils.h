// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameProjectUtils.h"

/**
 * Scaffold generation utilities.
 */
class FGBAScaffoldUtils
{
public:
	
	static GameProjectUtils::EAddCodeToProjectResult AddClassToProject(
		const FString& InNewClassName,
		const FString& InNewClassPath,
		const FString& InHeaderDestination,
		const FString& InHeaderContent,
		const FString& InSourceDestination,
		const FString& InSourceContent,
		const FModuleContextInfo& InModuleInfo,
		GameProjectUtils::EReloadStatus& OutReloadStatus,
		FText& OutErrorText
	);

	static GameProjectUtils::EAddCodeToProjectResult AddCodeFileToProject(const FString& InDestination, const FString& InContent, FText& OutErrorText);

	static bool UpdateProjectFiles(FText& ErrorText);

	//~ Begin GameProjectUtils fallback - Those methods are private
	/** Creates the basic source code for a new project. On failure, OutFailReason will be populated. */
	static bool GenerateBasicSourceCode(
		const FString& NewProjectSourcePath,
		const FString& NewProjectName,
		TArray<FString>& OutGeneratedStartupModuleNames,
		TArray<FString>& OutCreatedFiles,
		FText& OutFailReason
	);

	/** Generates a Target.cs file for a game module */
	static bool GenerateGameModuleTargetFile(const FString& NewTargetFileName, const FString& ModuleName, const TArray<FString>& ExtraModuleNames, FText& OutFailReason);

	/** Generates a Build.cs file for a Editor module */
	static bool GenerateEditorModuleBuildFile(
		const FString& InNewBuildFileName,
		const FString& InModuleName,
		const TArray<FString>& OutPublicDependencyModuleNames,
		const TArray<FString>& OutPrivateDependencyModuleNames,
		FText& OutFailReason
	);

	/** Generates a Target.cs file for a Editor module */
	static bool GenerateEditorModuleTargetFile(const FString& NewTargetFileName, const FString& ModuleName, const TArray<FString>& ExtraModuleNames, FText& OutFailReason);

	/** Generates a main game module cpp file */
	static bool GenerateGameModuleCPPFile(const FString& NewGameModuleCPPFileName, const FString& ModuleName, const FString& GameName, FText& OutFailReason);
	
	/** Generates a main game module header file */
	static bool GenerateGameModuleHeaderFile(const FString& NewGameModuleHeaderFileName, const TArray<FString>& PublicHeaderIncludes, FText& OutFailReason);
	
	/** Returns the copyright line used at the top of all files */
	static FString MakeCopyrightLine();
	//~ End GameProjectUtils fallback

	static FString GetModuleBuildCSFilename(const FModuleContextInfo& InModuleContextInfo);
	
	static FString GetModuleBuildCSFilePath(const FModuleContextInfo& InModuleContextInfo);
	
	static bool DoesBuildCSFileContains(const FModuleContextInfo& InModuleContextInfo, const FString& InSearchPattern, FText& OutFailReason);
	
	static bool DoesBuildCSSatisfiesDependencies(const FModuleContextInfo& InModuleContextInfo, const TArray<FString>& InModuleDependencies, TArray<FString>& OutMissingModuleDependencies, FText& OutFailReason);
	
	static FString GetContainingModuleName(const UStruct* InStruct);
};
