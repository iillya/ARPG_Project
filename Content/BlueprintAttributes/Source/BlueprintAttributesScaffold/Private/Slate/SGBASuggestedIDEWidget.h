// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlateFwd.h"
#include "Layout/Visibility.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Input/Reply.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"

/**
 * Either a button to directly install or a hyperlink to a website to download the suggested IDE for the platform.
 * Only visible when no compiler is available.
 */
class SGBASuggestedIDEWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGBASuggestedIDEWidget)
	{}
		SLATE_ATTRIBUTE(EVisibility, VisibilityOverride)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	
private:
	static constexpr const TCHAR* DocumentationURL = TEXT("https://docs.unrealengine.com/5.0/en-US/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine/");
	
	/** Creates the appropriate widget to display for the platform */
	TSharedRef<SWidget> CreateGetSuggestedIDEWidget();
	
	/** Creates the appropriate widget to display for the platform */
	TSharedRef<SWidget> CreateGetDocumentationLinkWidget() const;

	/** Gets the visibility of the global error label IDE Link */
	static EVisibility GetVisibility();

	/** Handler for when the error label IDE hyperlink was clicked */
	static FReply OnDownloadIDEClicked(FString InURL);
	
	/** Handler for when the error label IDE hyperlink was clicked */
	static FReply OnRedirectToDocumentation();

	/** Handler for when the install IDE button was clicked */
	FReply OnInstallIDEClicked();

	/** Handler for when the suggested IDE installer has finished downloading */
	static void OnIDEInstallerDownloadComplete(bool bWasSuccessful);

	/** Handle to the notification displayed when downloading an IDE installer */
	static TSharedPtr<SNotificationItem> IDEDownloadNotification;
};