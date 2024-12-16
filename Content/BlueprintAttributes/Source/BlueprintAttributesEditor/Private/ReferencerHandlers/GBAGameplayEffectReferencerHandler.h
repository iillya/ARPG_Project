// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/EngineVersionComparison.h"
#include "ReferencerHandlers/IGBAAttributeReferencerHandler.h"
#include "UObject/WeakFieldPtr.h"

#if UE_VERSION_NEWER_THAN(5, 2, -1)
#include "AssetRegistry/AssetIdentifier.h"
#else
#include "AssetRegistry/AssetData.h"
#endif

class UGameplayEffect;
struct FAttributeBasedFloat;
struct FGameplayAttribute;
struct FGameplayEffectCue;
struct FGameplayEffectModifierMagnitude;
struct FGameplayEffectQuery;
struct FGameplayModifierInfo;

/**
 * Handlers for attribute renames on Gameplay Effect CDO.
 *
 * List of Attributes properties:
 *
 * - [x] Duration Magnitude > Attribute Based Magnitude > Backing Attribute > Attribute to Capture
 * - [x] Modifiers (FGameplayModifierInfo.Attribute) 
 *   - [x] Attribute Based Magnitude calculation type > Backing Attribute > Attribute to Capture
 * - [x] Gameplay Cues > Magnitude Attribute
 * - [x] Tags > Remove Gameplay Effect Query > Modifying Attribute
 * - [ ] Immunity > Granted Application Immunity Query > Modifying Attribute
 */
class FGBAGameplayEffectReferencerHandler : public IGBAAttributeReferencerHandler
{
public:

	/** Data holder for GE Modifier properties that needs an update */
	struct FAttributeModifierToReplace
	{
		int32 Index = 0;
		TWeakFieldPtr<FProperty> Property = nullptr;

		FAttributeModifierToReplace(const int32 Index, FProperty* Property)
			: Index(Index)
			, Property(Property)
		{
		}
	};

	enum class EAttributeReferenceType
	{
		/** Represents attribute-based duration */
		DurationMagnitude,
		
		/** Represents modifier Attribute */
		ModifierInfo_Attribute,
		
		/** Represents backing Attribute for a modifier */
		ModifierInfo_BackingAttribute_AttributeToCapture,
		
		/** Represents Magnitude Attribute for Gameplay Cues */
		GameplayCue_MagnitudeAttribute,
		
		/** Represents Modifying Attribute for Tags > RemoveGameplayEffectQuery */
		RemoveGameplayEffectQuery_ModifyingAttribute,

		/** Represents Modifying Attribute for Immunity > GrantedApplicationImmunityQuery */
		GrantedApplicationImmunityQuery_ModifyingAttribute,

		/** Default value */
		Unknown
	};

	/** Data holder for cache map, representing a reference to a FGameplayAttribute property in a GE DefaultObject */
	struct FAttributeReference
	{
		FString PackageNameOwner;
		FString AttributeName;
		int32 Index = -1;

		EAttributeReferenceType Type = EAttributeReferenceType::Unknown;

		FAttributeReference() = default;
	};

	static TSharedPtr<IGBAAttributeReferencerHandler> Create();
	virtual ~FGBAGameplayEffectReferencerHandler() override;

	//~ Begin IGBAAttributeReferencerHandler
	virtual void OnPreCompile(const FString& InPackageName) override;
	virtual void OnPostCompile(const FString& InPackageName) override;
	virtual bool HandlePreCompile(const FAssetIdentifier& InAssetIdentifier, const FGBAAttributeReferencerPayload& InPayload) override;
	virtual bool HandleAttributeRename(const FAssetIdentifier& InAssetIdentifier, const FGBAAttributeReferencerPayload& InPayload, TArray<TSharedRef<FTokenizedMessage>>& OutMessages) override;
	//~ End IGBAAttributeReferencerHandler

protected:
	TMap<FAssetIdentifier, TArray<FAttributeReference>> AttributesCacheMap;

	/**
	 * Parses and returns an "Attribute Reference" for the given struct found in a Gameplay Effect CDO.
	 *
	 * This description applies to all methods Build...()
	 *
	 * @return True whether we were able to find a valid attribute
	 */
	static bool BuildModifierInfoAttributeReference(const FGameplayModifierInfo& InModifier, FAttributeReference& OutAttributeReference);
	static bool BuildModifierMagnitudeAttributeReference(const FGameplayEffectModifierMagnitude& InMagnitude, FAttributeReference& OutAttributeReference);
	static bool BuildEffectCueMagnitudeAttributeReference(const FGameplayEffectCue& InEffectCue, FAttributeReference& OutAttributeReference);
	static bool BuildEffectQueryAttributeReference(const FGameplayEffectQuery& InEffectQuery, FAttributeReference& OutAttributeReference);
	
	/**
	 * Updates a Gameplay Effect CDO and changes property references for an Attribute from OldPropertyName to NewPropertyName.
	 *
	 * Returns true if it updated something and asset needs a modify / save.
	 *
	 * This description applies to all methods UpdateGameplayEffect...() below
	 *
	 * @param InEffectCDO Gameplay Effect CDO to modify
	 * @param InBlueprint UBlueprint for the AttributeSet containing the attribute that was renamed
	 * @param InAssetIdentifier Asset Identifier (as returned by Asset Registry) for the asset referencer (in this case Gameplay Effects) 
	 * @param InPayload Payload containing information such as referencer Default Object, Package Name of the Attribute Set and old / new variable name for the attribute renamed
	 * @param OutMessages A list of tokenized messages to display at the end of the rename and update of the attribute reference handling
	 *
	 * @return True if the Effect CDO was modified, false otherwise
	 */
	virtual bool UpdateModifiers(UGameplayEffect* InEffectCDO, const UBlueprint* InBlueprint, const FAssetIdentifier& InAssetIdentifier, const FGBAAttributeReferencerPayload& InPayload, TArray<TSharedRef<FTokenizedMessage>>& OutMessages);
	virtual bool UpdateModifiersBackingAttribute(UGameplayEffect* InEffectCDO, const UBlueprint* InBlueprint, const FAssetIdentifier& InAssetIdentifier, const FGBAAttributeReferencerPayload& InPayload, TArray<TSharedRef<FTokenizedMessage>>& OutMessages);
	virtual bool UpdateDuration(UGameplayEffect* InEffectCDO, const UBlueprint* InBlueprint, const FAssetIdentifier& InAssetIdentifier, const FGBAAttributeReferencerPayload& InPayload, TArray<TSharedRef<FTokenizedMessage>>& OutMessages);
	virtual bool UpdateCues(UGameplayEffect* InEffectCDO, const UBlueprint* InBlueprint, const FAssetIdentifier& InAssetIdentifier, const FGBAAttributeReferencerPayload& InPayload, TArray<TSharedRef<FTokenizedMessage>>& OutMessages);
	virtual bool UpdateRemoveGameplayEffectQuery(UGameplayEffect* InEffectCDO, const UBlueprint* InBlueprint, const FAssetIdentifier& InAssetIdentifier, const FGBAAttributeReferencerPayload& InPayload, TArray<TSharedRef<FTokenizedMessage>>& OutMessages);
	virtual bool UpdateImmunityEffectQuery(UGameplayEffect* InEffectCDO, const UBlueprint* InBlueprint, const FAssetIdentifier& InAssetIdentifier, const FGBAAttributeReferencerPayload& InPayload, TArray<TSharedRef<FTokenizedMessage>>& OutMessages);

	/** Common update code shared between Tags Remove Effect Query and Immunity Granted Application Query*/
	virtual bool UpdateEffectQuery(
		const UBlueprint* InBlueprint,
		const FAssetIdentifier& InAssetIdentifier,
		EAttributeReferenceType InReferenceType,
		const FGBAAttributeReferencerPayload& InPayload,
		const FText& InMessageText,
		FGameplayAttribute& OutModifyingAttribute,
		TArray<TSharedRef<FTokenizedMessage>>& OutMessages
	);

	FAttributeBasedFloat* GetAttributeBasedFloatFromContainer(FGameplayEffectModifierMagnitude* InModifierMagnitude) const;

	template <typename Predicate>
	bool GetCachedAttributeByPredicate(const FAssetIdentifier& InAssetIdentifier, FAttributeReference& OutAttributeReference, Predicate InPred)
	{
		if (!AttributesCacheMap.Contains(InAssetIdentifier))
		{
			return false;
		}

		TArray<FAttributeReference> Modifiers = AttributesCacheMap.FindChecked(InAssetIdentifier);
		FAttributeReference* FoundElement = Modifiers.FindByPredicate(InPred);

		if (!FoundElement)
		{
			return false;
		}

		OutAttributeReference = MoveTemp(*FoundElement);
		return true;
	}

	static FString GetClassDefaultName(const FString& InName);
};
