// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.


#include "GBAScaffoldUtils.h"

#include "DesktopPlatformModule.h"
#include "GeneralProjectSettings.h"
#include "ISourceControlModule.h"
#include "ISourceControlProvider.h"
#include "SourceCodeNavigation.h"
#include "SourceControlOperations.h"
#include "Misc/App.h"
#include "Misc/FileHelper.h"
#include "Misc/MessageDialog.h"
#include "Misc/Paths.h"
#include "Misc/ScopedSlowTask.h"
#include "UObject/Package.h"

#if WITH_LIVE_CODING
#include "ILiveCodingModule.h"
#endif

#define LOCTEXT_NAMESPACE "GBAScaffoldUtils"

GameProjectUtils::EAddCodeToProjectResult FGBAScaffoldUtils::AddClassToProject(
	const FString& InNewClassName,
	const FString& InNewClassPath,
	const FString& InHeaderDestination,
	const FString& InHeaderContent,
	const FString& InSourceDestination,
	const FString& InSourceContent,
	const FModuleContextInfo& InModuleInfo,
	GameProjectUtils::EReloadStatus& OutReloadStatus,
	FText& OutErrorText
)
{
	const TSet<FString> DisallowedHeaderNames;
	if (!GameProjectUtils::IsValidClassNameForCreation(InNewClassName, InModuleInfo, DisallowedHeaderNames, OutErrorText))
	{
		return GameProjectUtils::EAddCodeToProjectResult::InvalidInput;
	}

	if (!FApp::HasProjectName())
	{
		OutErrorText = LOCTEXT("AddCodeToProject_NoGameName", "You can not add code because you have not loaded a project.");
		return GameProjectUtils::EAddCodeToProjectResult::FailedToAddCode;
	}

	FString NewCppPath;
	FString NewHeaderPath;
	if (!GameProjectUtils::CalculateSourcePaths(InNewClassPath, InModuleInfo, NewHeaderPath, NewCppPath, &OutErrorText))
	{
		return GameProjectUtils::EAddCodeToProjectResult::FailedToAddCode;
	}

	if (!InHeaderDestination.StartsWith(NewHeaderPath))
	{
		OutErrorText = FText::Format(
			LOCTEXT("HeaderPathMismatched", "NewHeaderPath returned by GameProjectUtils::CalculateSourcePaths is different than provided destination\n\t HeaderPath: {0}\n\t Destination: {1}"),
			FText::FromString(NewHeaderPath),
			FText::FromString(InHeaderDestination)
		);

		return GameProjectUtils::EAddCodeToProjectResult::FailedToAddCode;
	}

	if (!InSourceDestination.StartsWith(NewCppPath))
	{
		OutErrorText = FText::Format(
			LOCTEXT("HeaderPathMismatched", "NewCppPath returned by GameProjectUtils::CalculateSourcePaths is different than provided destination\n\t CppPath: {0}\n\t Destination: {1}"),
			FText::FromString(NewCppPath),
			FText::FromString(InSourceDestination)
		);

		return GameProjectUtils::EAddCodeToProjectResult::FailedToAddCode;
	}

	FScopedSlowTask SlowTask(5.f, LOCTEXT("AddingCodeToProject", "Adding code to project..."));
	SlowTask.MakeDialog();

	SlowTask.EnterProgressFrame(1.0f, LOCTEXT("CompilingCPlusPlusCode", "Compiling new C++ code. Please wait..."));

	// TODO: Update project file ? (eg. if project has no code files, generate basic code with Build.cs etc.)
	// if (!UpdateProjectFiles(ErrorText)) { return GameProjectUtils::EAddCodeToProjectResult::FailedToAddCode; }
	// SlowTask.EnterProgressFrame(1.0f, LOCTEXT("CompilingCPlusPlusCode", "Compiling new C++ code. Please wait..."));

	TArray<FString> CreatedFiles;

	// Class Header File
	{
		const GameProjectUtils::EAddCodeToProjectResult Result = AddCodeFileToProject(InHeaderDestination, InHeaderContent, OutErrorText);
		if (Result != GameProjectUtils::EAddCodeToProjectResult::Succeeded)
		{
			return Result;
		}

		CreatedFiles.Add(InHeaderDestination);
	}

	SlowTask.EnterProgressFrame(1.0f, LOCTEXT("CompilingCPlusPlusCode", "Compiling new C++ code. Please wait..."));

	// Class CPP file
	{
		const GameProjectUtils::EAddCodeToProjectResult Result = AddCodeFileToProject(InSourceDestination, InSourceContent, OutErrorText);
		if (Result != GameProjectUtils::EAddCodeToProjectResult::Succeeded)
		{
			return Result;
		}

		CreatedFiles.Add(InSourceDestination);
	}

	SlowTask.EnterProgressFrame(1.0f, LOCTEXT("CompilingCPlusPlusCode", "Compiling new C++ code. Please wait..."));


	const bool bProjectHadCodeFiles = GameProjectUtils::ProjectHasCodeFiles();
	bool bGenerateProjectFiles = true;

	TArray<FString> CreatedFilesForExternalAppRead;
	CreatedFilesForExternalAppRead.Reserve(CreatedFiles.Num());
	for (const FString& CreatedFile : CreatedFiles)
	{
		CreatedFilesForExternalAppRead.Add(IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*CreatedFile));
	}

	// First see if we can avoid a full generation by adding the new files to an already open project
	if (bProjectHadCodeFiles && FSourceCodeNavigation::AddSourceFiles(CreatedFilesForExternalAppRead))
	{
		// We managed the gather, so we can skip running the full generate
		bGenerateProjectFiles = false;
	}

	if (bGenerateProjectFiles)
	{
		// Generate project files if we happen to be using a project file.
		if (!FDesktopPlatformModule::Get()->GenerateProjectFiles(FPaths::RootDir(), FPaths::GetProjectFilePath(), GWarn))
		{
			OutErrorText = LOCTEXT("FailedToGenerateProjectFiles", "Failed to generate project files.");
			return GameProjectUtils::EAddCodeToProjectResult::FailedToHotReload;
		}
	}

	SlowTask.EnterProgressFrame(1.0f, LOCTEXT("CompilingCPlusPlusCode", "Compiling new C++ code. Please wait..."));

	// Mark the files for add in SCC
	ISourceControlProvider& SourceControlProvider = ISourceControlModule::Get().GetProvider();
	if (ISourceControlModule::Get().IsEnabled() && SourceControlProvider.IsAvailable())
	{
		SourceControlProvider.Execute(ISourceControlOperation::Create<FMarkForAdd>(), CreatedFilesForExternalAppRead);
	}

	SlowTask.EnterProgressFrame(1.0f, LOCTEXT("CompilingCPlusPlusCode", "Compiling new C++ code. Please wait..."));

#if WITH_LIVE_CODING
	ILiveCodingModule* LiveCoding = FModuleManager::GetModulePtr<ILiveCodingModule>(LIVE_CODING_MODULE_NAME);
	if (LiveCoding != nullptr && LiveCoding->IsEnabledForSession())
	{
		if (!bProjectHadCodeFiles)
		{
			FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("LiveCodingNoSources", "Project now includes sources, please close the editor and build from your IDE."));
			return GameProjectUtils::EAddCodeToProjectResult::Succeeded;
		}

		if (LiveCoding->AutomaticallyCompileNewClasses())
		{
			LiveCoding->Compile(ELiveCodingCompileFlags::None, nullptr);
			OutReloadStatus = GameProjectUtils::EReloadStatus::Reloaded;
		}
		return GameProjectUtils::EAddCodeToProjectResult::Succeeded;
	}
#endif

	if (!bProjectHadCodeFiles)
	{
		// This is the first time we add code to this project, so notify user
		// GameProjectUtils is doing hot reloading here, but we don't want to rely on HotReload
		// TODO: Proper game code / framework generation on BP only projects
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("HotReloadNoSources", "Project now includes sources, please close the editor and build from your IDE."));
		return GameProjectUtils::EAddCodeToProjectResult::Succeeded;
	}
	

	return GameProjectUtils::EAddCodeToProjectResult::Succeeded;
}

GameProjectUtils::EAddCodeToProjectResult FGBAScaffoldUtils::AddCodeFileToProject(const FString& InDestination, const FString& InContent, FText& OutErrorText)
{
	// Generate
	if (GameProjectUtils::WriteOutputFile(InDestination, InContent, OutErrorText))
	{
		return GameProjectUtils::EAddCodeToProjectResult::Succeeded;
	}
	
	return GameProjectUtils::EAddCodeToProjectResult::FailedToAddCode;
}

bool FGBAScaffoldUtils::UpdateProjectFiles(FText& ErrorText)
{
	TArray<FString> CreatedFiles;
	TArray<FString> StartupModuleNames;

	const bool bProjectHadCodeFiles = GameProjectUtils::ProjectHasCodeFiles();
	bool bUpdateProjectModules = false;
	if (!bProjectHadCodeFiles)
	{
		// Delete any generated intermediate code files. This ensures that blueprint projects with custom build settings can be converted to code projects without causing errors.
		IFileManager::Get().DeleteDirectory(*(FPaths::ProjectIntermediateDir() / TEXT("Source")), false, true);

		// We always add the basic source code to the root directory, not the potential sub-directory provided by NewClassPath
		const FString SourceDir = FPaths::GameSourceDir().LeftChop(1); // Trim the trailing /

		// Assuming the game name is the same as the primary game module name
		const FString GameModuleName = FApp::GetProjectName();

		if (GenerateBasicSourceCode(SourceDir, GameModuleName, StartupModuleNames, CreatedFiles, ErrorText))
		{
			bUpdateProjectModules = true;
		}
		else
		{
			GameProjectUtils::DeleteCreatedFiles(SourceDir, CreatedFiles);
			bUpdateProjectModules = false;
		}
	}

	return bUpdateProjectModules;
}

bool FGBAScaffoldUtils::GenerateBasicSourceCode(const FString& NewProjectSourcePath, const FString& NewProjectName, TArray<FString>& OutGeneratedStartupModuleNames, TArray<FString>& OutCreatedFiles, FText& OutFailReason)
{
	const FString GameModulePath = NewProjectSourcePath / NewProjectName;
	const FString EditorName = NewProjectName + TEXT("Editor");

	// MyGame.Build.cs
	{
		const FString NewBuildFilename = GameModulePath / NewProjectName + TEXT(".Build.cs");
		TArray<FString> PublicDependencyModuleNames;
		PublicDependencyModuleNames.Add(TEXT("Core"));
		PublicDependencyModuleNames.Add(TEXT("CoreUObject"));
		PublicDependencyModuleNames.Add(TEXT("Engine"));
		PublicDependencyModuleNames.Add(TEXT("InputCore"));
		const TArray<FString> PrivateDependencyModuleNames;
		if (GameProjectUtils::GenerateGameModuleBuildFile(NewBuildFilename, NewProjectName, PublicDependencyModuleNames, PrivateDependencyModuleNames, OutFailReason))
		{
			OutGeneratedStartupModuleNames.Add(NewProjectName);
			OutCreatedFiles.Add(NewBuildFilename);
		}
		else
		{
			return false;
		}
	}

	// MyGame.Target.cs
	{
		const FString NewTargetFilename = NewProjectSourcePath / NewProjectName + TEXT(".Target.cs");
		TArray<FString> ExtraModuleNames;
		ExtraModuleNames.Add(NewProjectName);
		if (GenerateGameModuleTargetFile(NewTargetFilename, NewProjectName, ExtraModuleNames, OutFailReason))
		{
			OutCreatedFiles.Add(NewTargetFilename);
		}
		else
		{
			return false;
		}
	}

	// MyGameEditor.Target.cs
	{
		const FString NewTargetFilename = NewProjectSourcePath / EditorName + TEXT(".Target.cs");
		// Include the MyGame module...
		TArray<FString> ExtraModuleNames;
		ExtraModuleNames.Add(NewProjectName);
		if (GenerateEditorModuleTargetFile(NewTargetFilename, EditorName, ExtraModuleNames, OutFailReason))
		{
			OutCreatedFiles.Add(NewTargetFilename);
		}
		else
		{
			return false;
		}
	}

	// MyGame.h
	{
		const FString NewHeaderFilename = GameModulePath / NewProjectName + TEXT(".h");
		const TArray<FString> PublicHeaderIncludes;
		if (GenerateGameModuleHeaderFile(NewHeaderFilename, PublicHeaderIncludes, OutFailReason))
		{
			OutCreatedFiles.Add(NewHeaderFilename);
		}
		else
		{
			return false;
		}
	}

	// MyGame.cpp
	{
		const FString NewCPPFilename = GameModulePath / NewProjectName + TEXT(".cpp");
		if (GenerateGameModuleCPPFile(NewCPPFilename, NewProjectName, NewProjectName, OutFailReason))
		{
			OutCreatedFiles.Add(NewCPPFilename);
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool FGBAScaffoldUtils::GenerateGameModuleTargetFile(const FString& NewTargetFileName, const FString& ModuleName, const TArray<FString>& ExtraModuleNames, FText& OutFailReason)
{
	FString Template;
	if (!GameProjectUtils::ReadTemplateFile(TEXT("Stub.Target.cs.template"), Template, OutFailReason))
	{
		return false;
	}

	FString FinalOutput = Template.Replace(TEXT("%COPYRIGHT_LINE%"), *MakeCopyrightLine(), ESearchCase::CaseSensitive);
	FinalOutput = FinalOutput.Replace(TEXT("%EXTRA_MODULE_NAMES%"), *GameProjectUtils::MakeCommaDelimitedList(ExtraModuleNames), ESearchCase::CaseSensitive);
	FinalOutput = FinalOutput.Replace(TEXT("%MODULE_NAME%"), *ModuleName, ESearchCase::CaseSensitive);
	FinalOutput = FinalOutput.Replace(TEXT("%TARGET_TYPE%"), TEXT("Game"), ESearchCase::CaseSensitive);
	FinalOutput = FinalOutput.Replace(TEXT("%DEFAULT_BUILD_SETTINGS_VERSION%"), GameProjectUtils::GetDefaultBuildSettingsVersion(), ESearchCase::CaseSensitive);

	return GameProjectUtils::WriteOutputFile(NewTargetFileName, FinalOutput, OutFailReason);
}

bool FGBAScaffoldUtils::GenerateEditorModuleBuildFile(const FString& InNewBuildFileName, const FString& InModuleName, const TArray<FString>& OutPublicDependencyModuleNames, const TArray<FString>& OutPrivateDependencyModuleNames, FText& OutFailReason)
{
	FString Template;
	if (!GameProjectUtils::ReadTemplateFile(TEXT("EditorModule.Build.cs.template"), Template, OutFailReason))
	{
		return false;
	}

	FString FinalOutput = Template.Replace(TEXT("%COPYRIGHT_LINE%"), *MakeCopyrightLine(), ESearchCase::CaseSensitive);
	FinalOutput = FinalOutput.Replace(TEXT("%PUBLIC_DEPENDENCY_MODULE_NAMES%"), *GameProjectUtils::MakeCommaDelimitedList(OutPublicDependencyModuleNames), ESearchCase::CaseSensitive);
	FinalOutput = FinalOutput.Replace(TEXT("%PRIVATE_DEPENDENCY_MODULE_NAMES%"), *GameProjectUtils::MakeCommaDelimitedList(OutPrivateDependencyModuleNames), ESearchCase::CaseSensitive);
	FinalOutput = FinalOutput.Replace(TEXT("%MODULE_NAME%"), *InModuleName, ESearchCase::CaseSensitive);

	GameProjectUtils::ResetCurrentProjectModulesCache();

	return GameProjectUtils::WriteOutputFile(InNewBuildFileName, FinalOutput, OutFailReason);
}

bool FGBAScaffoldUtils::GenerateEditorModuleTargetFile(const FString& NewTargetFileName, const FString& ModuleName, const TArray<FString>& ExtraModuleNames, FText& OutFailReason)
{
	FString Template;
	if (!GameProjectUtils::ReadTemplateFile(TEXT("Stub.Target.cs.template"), Template, OutFailReason))
	{
		return false;
	}

	FString FinalOutput = Template.Replace(TEXT("%COPYRIGHT_LINE%"), *MakeCopyrightLine(), ESearchCase::CaseSensitive);
	FinalOutput = FinalOutput.Replace(TEXT("%EXTRA_MODULE_NAMES%"), *GameProjectUtils::MakeCommaDelimitedList(ExtraModuleNames), ESearchCase::CaseSensitive);
	FinalOutput = FinalOutput.Replace(TEXT("%MODULE_NAME%"), *ModuleName, ESearchCase::CaseSensitive);
	FinalOutput = FinalOutput.Replace(TEXT("%TARGET_TYPE%"), TEXT("Editor"), ESearchCase::CaseSensitive);
	FinalOutput = FinalOutput.Replace(TEXT("%DEFAULT_BUILD_SETTINGS_VERSION%"), GameProjectUtils::GetDefaultBuildSettingsVersion(), ESearchCase::CaseSensitive);

	return GameProjectUtils::WriteOutputFile(NewTargetFileName, FinalOutput, OutFailReason);
}

bool FGBAScaffoldUtils::GenerateGameModuleCPPFile(const FString& NewGameModuleCPPFileName, const FString& ModuleName, const FString& GameName, FText& OutFailReason)
{
	FString Template;
	if (!GameProjectUtils::ReadTemplateFile(TEXT("GameModule.cpp.template"), Template, OutFailReason))
	{
		return false;
	}

	FString FinalOutput = Template.Replace(TEXT("%COPYRIGHT_LINE%"), *MakeCopyrightLine(), ESearchCase::CaseSensitive);
	FinalOutput = FinalOutput.Replace(TEXT("%MODULE_NAME%"), *ModuleName, ESearchCase::CaseSensitive);
	FinalOutput = FinalOutput.Replace(TEXT("%GAME_NAME%"), *GameName, ESearchCase::CaseSensitive);

	return GameProjectUtils::WriteOutputFile(NewGameModuleCPPFileName, FinalOutput, OutFailReason);
}

bool FGBAScaffoldUtils::GenerateGameModuleHeaderFile(const FString& NewGameModuleHeaderFileName, const TArray<FString>& PublicHeaderIncludes, FText& OutFailReason)
{
	FString Template;
	if (!GameProjectUtils::ReadTemplateFile(TEXT("GameModule.h.template"), Template, OutFailReason))
	{
		return false;
	}

	FString FinalOutput = Template.Replace(TEXT("%COPYRIGHT_LINE%"), *MakeCopyrightLine(), ESearchCase::CaseSensitive);
	FinalOutput = FinalOutput.Replace(TEXT("%PUBLIC_HEADER_INCLUDES%"), *GameProjectUtils::MakeIncludeList(PublicHeaderIncludes), ESearchCase::CaseSensitive);

	return GameProjectUtils::WriteOutputFile(NewGameModuleHeaderFileName, FinalOutput, OutFailReason);
}

FString FGBAScaffoldUtils::MakeCopyrightLine()
{
	const FString CopyrightNotice = GetDefault<UGeneralProjectSettings>()->CopyrightNotice;
	if (!CopyrightNotice.IsEmpty())
	{
		return FString(TEXT("// ")) + CopyrightNotice;
	}

	return FString();
}

FString FGBAScaffoldUtils::GetModuleBuildCSFilename(const FModuleContextInfo& InModuleContextInfo)
{
	return FString::Printf(TEXT("%s.Build.cs"), *InModuleContextInfo.ModuleName);
}

FString FGBAScaffoldUtils::GetModuleBuildCSFilePath(const FModuleContextInfo& InModuleContextInfo)
{
	return InModuleContextInfo.ModuleSourcePath / GetModuleBuildCSFilename(InModuleContextInfo);
}

bool FGBAScaffoldUtils::DoesBuildCSFileContains(const FModuleContextInfo& InModuleContextInfo, const FString& InSearchPattern, FText& OutFailReason)
{
	const FString FileName = GetModuleBuildCSFilePath(InModuleContextInfo);

	// Read the file to a string
	FString FileContents;
	if (!FFileHelper::LoadFileToString(FileContents, *FileName))
	{
		OutFailReason = FText::FromString(FString::Printf(TEXT("Failed to open descriptor file %s"), *FileName));
		return false;
	}

	return FileContents.Contains(InSearchPattern);
}

bool FGBAScaffoldUtils::DoesBuildCSSatisfiesDependencies(const FModuleContextInfo& InModuleContextInfo, const TArray<FString>& InModuleDependencies, TArray<FString>& OutMissingModuleDependencies, FText& OutFailReason)
{
	TArray<FString> MissingModuleDependencies;
	for (const FString& ModuleDependency : InModuleDependencies)
	{
		FText ErrorText;
		const FString DependencySearchPattern = FString::Printf(TEXT("\"%s\""), *ModuleDependency);
		const bool bHasDependency = DoesBuildCSFileContains(InModuleContextInfo, DependencySearchPattern, ErrorText);

		if (!ErrorText.IsEmpty())
		{
			OutFailReason = ErrorText;
			return false;
		}
		
		if (!bHasDependency)
		{
			MissingModuleDependencies.Add(ModuleDependency);
		}
	}

	const bool bSatisfiesDependencies = MissingModuleDependencies.IsEmpty();
	OutMissingModuleDependencies = MoveTemp(MissingModuleDependencies);
	return bSatisfiesDependencies;
}

FString FGBAScaffoldUtils::GetContainingModuleName(const UStruct* InStruct)
{
	check(InStruct);

	const UPackage* Package = InStruct->GetOutermost();
	check(Package);

	FString PackageName = Package->GetName();
	PackageName.RemoveFromStart(TEXT("/Script/"));
	return PackageName;
}

#undef LOCTEXT_NAMESPACE
