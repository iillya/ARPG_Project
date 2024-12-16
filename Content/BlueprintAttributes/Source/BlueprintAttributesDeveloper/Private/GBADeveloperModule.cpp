// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBADeveloperModule.h"

#include "BlueprintGraph/ReferencerHandlers/FGBASwitchNodeReferencerHandler.h"
#include "Subsystems/GBAEditorSubsystem.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

#define LOCTEXT_NAMESPACE "FGBADeveloperModule"

void FGBADeveloperModule::StartupModule()
{
	FCoreDelegates::OnPostEngineInit.AddRaw(this, &FGBADeveloperModule::HandlePostEngineInit);
}

void FGBADeveloperModule::ShutdownModule()
{
	FCoreDelegates::OnPostEngineInit.RemoveAll(this);
	
	if (GEditor)
	{
		UGBAEditorSubsystem::Get().UnregisterReferencerHandler(TEXT("GBAK2Node_SwitchGameplayAttribute"));
	}
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void FGBADeveloperModule::HandlePostEngineInit()
{
	if (GEditor)
	{
		UGBAEditorSubsystem::Get().RegisterReferencerHandler(TEXT("GBAK2Node_SwitchGameplayAttribute"), FGBASwitchNodeReferencerHandler::Create());
	}
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FGBADeveloperModule, BlueprintAttributesDeveloper)