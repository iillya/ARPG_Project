// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * This defines a set of helper functions declaring, accessing and initializing new ViewModel properties,
 * to avoid to manually write these functions.
 *
 * It would create the following functions and delegate, for attribute DisplayName:
 *
 *		DECLARE_MULTICAST_DELEGATE_OneParam(FOnDisplayNameChanged, const FString&);
 * 
 *		FString FMyModel::GetDisplayName() const;
 *		void FMyModel::SetDisplayName(const FString& InNewVal, const bool bTriggerDelegate = true);
 *		FOnSelectedClassPathChanged& FMyModel::OnSelectedClassPathChanged();
 *
 * Setter will invoke the multicast delegate by default, after value is changed. An additional bTriggerDelegate bool can be set to false
 * to prevent the delegate invocation.
 *
 * To use this you can define something like this:
 *
 *		DECLARE_VIEWMODEL_PROPERTY(FString, DisplayName);		
 */
#define DECLARE_VIEWMODEL_PROPERTY(PropertyType, PropertyName) \
	public: \
		DECLARE_MULTICAST_DELEGATE_TwoParams(FOn##PropertyName##Changed, const PropertyType&, const PropertyType&); \
		PropertyType Get##PropertyName() const \
		{ \
			return PropertyName;\
		} \
		void Set##PropertyName(const PropertyType& InNewValue, const bool bTriggerDelegate = true) \
		{ \
			PropertyType OldProperty = PropertyName; \
			PropertyName = InNewValue; \
			if (bTriggerDelegate) \
			{ \
				On##PropertyName##ChangedDelegate.Broadcast(OldProperty, InNewValue); \
				OnModelChangedDelegate.Broadcast(); \
				OnModelPropertyChangedDelegate.Broadcast(TEXT("" #PropertyName)); \
			}\
		} \
		FOn##PropertyName##Changed& On##PropertyName##Changed() { return On##PropertyName##ChangedDelegate; } \
	private: \
		PropertyType PropertyName; \
		FOn##PropertyName##Changed On##PropertyName##ChangedDelegate; \
	public:
	
/**
 * Implements a view model pattern for slate widgets.
 */
class BLUEPRINTATTRIBUTESEDITORCOMMON_API IGBASlateViewModel : public TSharedFromThis<IGBASlateViewModel>
{
public:
	/** Delegate called whenever one of the view model property is updated */
	DECLARE_MULTICAST_DELEGATE(FOnModelChanged);

	/** Delegate called whenever one of the view model property is updated (this one passes down the Property name that was changed) */
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnModelPropertyChanged, const FString&);

	/** Broadcasts whenever one of the view model property is updated */
	FOnModelChanged& OnModelChanged() { return OnModelChangedDelegate; }
	
	/** Broadcasts whenever one of the view model property is updated */
	FOnModelPropertyChanged& OnModelPropertyChanged() { return OnModelPropertyChangedDelegate; }

	/** Virtual destructor */
	virtual ~IGBASlateViewModel() {}

	/** Hook for initialization logic, can be noop */
	virtual void Initialize() = 0;

protected:
	/** Delegate invoked whenever one of the view model property is changed */
	FOnModelChanged OnModelChangedDelegate;

	/** Delegate invoked whenever one of the view model property is changed */
	FOnModelPropertyChanged OnModelPropertyChangedDelegate;
};
