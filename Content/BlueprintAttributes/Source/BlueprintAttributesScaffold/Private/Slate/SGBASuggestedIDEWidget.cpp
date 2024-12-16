// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "SGBASuggestedIDEWidget.h"
#include "HAL/PlatformProcess.h"
#include "SourceCodeNavigation.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "EngineAnalytics.h"
#include "Framework/Application/SlateApplication.h"
#include "Interfaces/IAnalyticsProvider.h"
#include "SPrimaryButton.h"

#define LOCTEXT_NAMESPACE "SGBASuggestedIDEWidget"

TSharedPtr<SNotificationItem> SGBASuggestedIDEWidget::IDEDownloadNotification;

void SGBASuggestedIDEWidget::Construct(const FArguments& InArgs)
{
	TAttribute<EVisibility> DefaultVisibility;
	DefaultVisibility.BindStatic(&SGBASuggestedIDEWidget::GetVisibility);
	SetVisibility(InArgs._VisibilityOverride.IsSet() ? InArgs._VisibilityOverride : DefaultVisibility);

	ChildSlot
	[
		// CreateGetSuggestedIDEWidget()
		CreateGetDocumentationLinkWidget()
	];
}

TSharedRef<SWidget> SGBASuggestedIDEWidget::CreateGetSuggestedIDEWidget()
{
	// TODO: Change Install IDE link to redirect to https://dev.epicgames.com/community/learning/tutorials/k8Ve/unreal-engine-how-to-build-the-unreal-editor-github
	// Or https://docs.unrealengine.com/5.0/en-US/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine/
	if (FSourceCodeNavigation::GetCanDirectlyInstallSourceCodeIDE())
	{
		// If the installer for this platform's IDE can be downloaded and launched directly, show a button
		return			
			SNew(SPrimaryButton)
			.Text(FText::Format(LOCTEXT("IDEInstallButtonText", "Install {0}"), FSourceCodeNavigation::GetSuggestedSourceCodeIDE()))
			.OnClicked(this, &SGBASuggestedIDEWidget::OnInstallIDEClicked);
	}
	
	return	
		SNew(SPrimaryButton)
		.Text(FText::Format(LOCTEXT("IDEDownloadLinkText", "Download {0}"), FSourceCodeNavigation::GetSuggestedSourceCodeIDE()))
		.OnClicked_Static(&SGBASuggestedIDEWidget::OnDownloadIDEClicked, FSourceCodeNavigation::GetSuggestedSourceCodeIDEDownloadURL());
}

TSharedRef<SWidget> SGBASuggestedIDEWidget::CreateGetDocumentationLinkWidget() const
{
	return	
		SNew(SPrimaryButton)
		.Text(FText::Format(LOCTEXT("IDESetupText", "Setting Up {0}"), FSourceCodeNavigation::GetSuggestedSourceCodeIDE()))
		.OnClicked_Static(&SGBASuggestedIDEWidget::OnRedirectToDocumentation);
}

EVisibility SGBASuggestedIDEWidget::GetVisibility()
{
	return FSourceCodeNavigation::IsCompilerAvailable() ? EVisibility::Collapsed : EVisibility::Visible;
}

FReply SGBASuggestedIDEWidget::OnDownloadIDEClicked(const FString InURL)
{
	FPlatformProcess::LaunchURL(*InURL, nullptr, nullptr);
	return FReply::Handled();
}

FReply SGBASuggestedIDEWidget::OnRedirectToDocumentation()
{
	FPlatformProcess::LaunchURL(DocumentationURL, nullptr, nullptr);
	return FReply::Handled();
}

FReply SGBASuggestedIDEWidget::OnInstallIDEClicked()
{
	// If the notification faded out, allow it to be deleted.
	if (IDEDownloadNotification.IsValid() && IDEDownloadNotification->GetCompletionState() == SNotificationItem::CS_None)
	{
		IDEDownloadNotification.Reset();
	}

	// If we have a notification already for this task and its corresponding task hasn't yet completed, do nothing.
	if (!IDEDownloadNotification.IsValid() || IDEDownloadNotification->GetCompletionState() != SNotificationItem::ECompletionState::CS_Pending)
	{
		const FText MessageText = FText::Format(LOCTEXT("DownloadingIDEInstaller", "Downloading {0} Installer..."), FSourceCodeNavigation::GetSuggestedSourceCodeIDE(true));

		if (!IDEDownloadNotification.IsValid())
		{
			FNotificationInfo Info(MessageText);
			Info.bUseLargeFont = false;
			Info.bFireAndForget = false;
			Info.bUseSuccessFailIcons = true;
			Info.bUseThrobber = true;

			IDEDownloadNotification = FSlateNotificationManager::Get().AddNotification(Info);
		}
		else
		{
			// Just reuse the same notification, since it hasn't faded offscreen yet.
			IDEDownloadNotification->SetText(MessageText);
		}
		IDEDownloadNotification->SetCompletionState(SNotificationItem::ECompletionState::CS_Pending);

		FSourceCodeNavigation::DownloadAndInstallSuggestedIDE(FOnIDEInstallerDownloadComplete::CreateStatic(&SGBASuggestedIDEWidget::OnIDEInstallerDownloadComplete));

		if (FEngineAnalytics::IsAvailable())
		{
			FEngineAnalytics::GetProvider().RecordEvent(TEXT("Editor.Usage.InstalledIDE"));
		}
	}


	const TSharedPtr<SWindow> ThisWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());
	if (ThisWindow.IsValid() && ThisWindow->IsModalWindow())
	{
		// If this window is modal, close it to unblock the IDE request and allow it to finish...as long as another
		// modal window isn't opened on top of it
		ThisWindow->RequestDestroyWindow();
	}

	return FReply::Handled();
}

void SGBASuggestedIDEWidget::OnIDEInstallerDownloadComplete(const bool bWasSuccessful)
{
	if (IDEDownloadNotification.IsValid())
	{
		if (bWasSuccessful)
		{
			IDEDownloadNotification->SetCompletionState(SNotificationItem::ECompletionState::CS_Success);
			IDEDownloadNotification->SetText(LOCTEXT("IDEDownloadSuccess", "Starting installation..."));
		}
		else
		{
			IDEDownloadNotification->SetCompletionState(SNotificationItem::ECompletionState::CS_Fail);
			IDEDownloadNotification->SetText(LOCTEXT("IDEDownloadFailure", "Failed to download installer. Please check your internet connection."));
		}

		IDEDownloadNotification->ExpireAndFadeout();
		IDEDownloadNotification = nullptr;
	}
}

#undef LOCTEXT_NAMESPACE
