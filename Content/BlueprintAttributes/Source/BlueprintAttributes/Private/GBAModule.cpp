// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBAModule.h"

#define LOCTEXT_NAMESPACE "FGBAModule"

void FGBAModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FGBAModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGBAModule, BlueprintAttributes)