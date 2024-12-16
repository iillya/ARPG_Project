// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "Styling/GBAEditorStyle.h"

#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

FGBAEditorStyle::FGBAEditorStyle()
	: FSlateStyleSet(TEXT("GBAEditorStyleSet"))
{
	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("BlueprintAttributes"));
	check(Plugin.IsValid());

	const FString PluginContentDir = FPaths::ConvertRelativePathToFull(FPaths::Combine(Plugin->GetBaseDir(), TEXT("Resources/Icons")));
	FSlateStyleSet::SetContentRoot(PluginContentDir);

	const FVector2D Icon16X16 = FVector2D(16.0);
	Set(
		"Icons.HeaderView",
		new FSlateVectorImageBrush(FSlateStyleSet::RootToContentDir("BlueprintHeader_16", TEXT(".svg")), Icon16X16)
	);

	FSlateStyleRegistry::RegisterSlateStyle(*this);
}

FGBAEditorStyle::~FGBAEditorStyle()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*this);
}
