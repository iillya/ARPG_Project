// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "Net/Core/PushModel/PushModelMacros.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Misc/EngineVersionComparison.h"

#if WITH_EDITOR
#include "EdGraph/EdGraphNode.h"

class UK2Node;
class UEdGraphPin;
#endif

#include "GBAAttributeSetBlueprintBase.generated.h"

/**
 * Structure holding various information to deal with AttributeSet lifecycle events (such as Pre/PostGameplayEffectExecute),
 * extracting info from FGameplayEffectModCallbackData.
 */
USTRUCT(BlueprintType)
struct BLUEPRINTATTRIBUTES_API FGBAAttributeSetExecutionData
{
	GENERATED_BODY()

	/** The physical representation of the Source ASC (The ability system component of the instigator that started the whole chain) */
	UPROPERTY(BlueprintReadOnly, Category = "Blueprint Attributes")
	TObjectPtr<AActor> SourceActor = nullptr;

	/** The physical representation of the owner (Avatar) for the target we intend to apply to  */
	UPROPERTY(BlueprintReadOnly, Category = "Blueprint Attributes")
	TObjectPtr<AActor> TargetActor = nullptr;

	/** The ability system component of the instigator that started the whole chain */
	UPROPERTY(BlueprintReadOnly, Category = "Blueprint Attributes")
	TObjectPtr<UAbilitySystemComponent> SourceASC = nullptr;

	/** The ability system component we intend to apply to */
	UPROPERTY(BlueprintReadOnly, Category = "Blueprint Attributes")
	TObjectPtr<UAbilitySystemComponent> TargetASC = nullptr;

	/** PlayerController associated with the owning actor for the Source ASC (The ability system component of the instigator that started the whole chain) */
	UPROPERTY(BlueprintReadOnly, Category = "Blueprint Attributes")
	TObjectPtr<APlayerController> SourceController = nullptr;

	/** PlayerController associated with the owning actor for the target we intend to apply to */
	UPROPERTY(BlueprintReadOnly, Category = "Blueprint Attributes")
	TObjectPtr<APlayerController> TargetController = nullptr;

	/** The object this effect was created from. */
	UPROPERTY(BlueprintReadOnly, Category = "Blueprint Attributes")
	TObjectPtr<UObject> SourceObject = nullptr;

	/** This tells us how we got here (who / what applied us) */
	UPROPERTY(BlueprintReadOnly, Category = "Blueprint Attributes")
	FGameplayEffectContextHandle Context;

	/** Combination of spec and actor tags for the captured Source Tags on GameplayEffectSpec creation */
	UPROPERTY(BlueprintReadOnly, Category = "Blueprint Attributes")
	FGameplayTagContainer SourceTags;

	/** All tags that apply to the gameplay effect spec */
	UPROPERTY(BlueprintReadOnly, Category = "Blueprint Attributes")
	FGameplayTagContainer SpecAssetTags;

	/** Holds the modifier magnitude value, if it is available (for scalable floats) */
	UPROPERTY(BlueprintReadOnly, Category = "Blueprint Attributes")
	float MagnitudeValue = 0.f;

	/** Holds the delta value between old and new, if it is available (for Additive Operations) */
	UPROPERTY(BlueprintReadOnly, Category = "Blueprint Attributes")
	float DeltaValue = 0.f;

	/** Default constructor */
	FGBAAttributeSetExecutionData() = default;

	/**
	 * Fills out FGBAAttributeSetExecutionData structure based on provided FGameplayEffectModCallbackData data.
	 *
	 * @param InModCallbackData The gameplay effect mod callback data available in attribute sets' Pre/PostGameplayEffectExecute
	 */
	explicit FGBAAttributeSetExecutionData(const FGameplayEffectModCallbackData& InModCallbackData);

	/** Returns a simple string representation for this structure */
	FString ToString(const FString& InSeparator = TEXT(", ")) const;
};

/** Enumeration outlining the possible gameplay effect magnitude calculation policies. */
UENUM()
enum class EGBAClampingType : uint8
{
	/** Clamping is disabled for this definition */
	None,
	
	/** Use a simple, static float for the clamping. */
	Float,
	
	/** Perform a clamping based upon another attribute. */
	AttributeBased,
};

USTRUCT()
struct BLUEPRINTATTRIBUTES_API FGBAClampDefinition
{
	GENERATED_BODY()
	
	/** Type of clamping to perform (either static float or attribute based) */
	UPROPERTY(EditDefaultsOnly, Category = "Clamp")
	EGBAClampingType ClampType = EGBAClampingType::Float;

	/** Float value to base the clamping on */
	UPROPERTY(EditDefaultsOnly, Category = "Clamp", meta=(EditConditionHides, EditCondition="ClampType == EGBAClampingType::Float"))
	float Value = 0.f;
	
	/**
	 * Gameplay Attribute to base the clamping on (for example, MaxHealth when clamping the Health attribute)
	 *
	 * Only "owned" attributes will be displayed here, meaning attributes that are part of the same Attribute Set class (eg. same owner)
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Clamp", meta=(EditConditionHides, EditCondition="ClampType == EGBAClampingType::AttributeBased", ShowOnlyOwnedAttributes))
	FGameplayAttribute Attribute;

	/** default constructor */
	FGBAClampDefinition() = default;
	virtual ~FGBAClampDefinition() = default;

	/** Returns string representation of all member variables of this struct */
	FString ToString() const
	{
		return FString::Printf(
			TEXT("ClampType: %s, Value: %f, Attribute: %s"),
			*UEnum::GetValueAsString(ClampType),
			Value,
			*Attribute.GetName()
		);
	}

	/** Returns the actual float value to use for the clamping, based on the ClampType used (eg. the backing attribute value or the static float) */
	float GetValueForClamping(const UAttributeSet* InOwnerSet) const;
	
	/**
	 * Returns the actual float value to use for the clamping, based on the ClampType used (eg. the backing attribute value or the static float)
	 *
	 * Function return value indicate whether the clamp definition is valid, eg. if attribute based attribute is valid for instance
	 */
	bool GetValueForClamping(const UAttributeSet* InOwnerSet, float& OutValue) const;
};

/**
 * Place in a Blueprint AttributeSet to create an attribute that can be accessed using FGameplayAttribute.
 *
 * This one has clamping functionality built-in (compared to FGameplayAttributeData)
 */
USTRUCT(DisplayName="Gameplay Clamped Attribute Data")
struct BLUEPRINTATTRIBUTES_API FGBAGameplayClampedAttributeData : public FGameplayAttributeData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Min")
	FGBAClampDefinition MinValue;
	
	UPROPERTY(EditDefaultsOnly, Category = "Max")
	FGBAClampDefinition MaxValue;

	FGBAGameplayClampedAttributeData() = default;

	explicit FGBAGameplayClampedAttributeData(const float DefaultValue)
		: FGameplayAttributeData(DefaultValue)
	{
	}
};

/**
 * Defines the set of all GameplayAttributes for your game.
 * 
 * Games should subclass this and add FGameplayAttributeData properties to represent attributes like health, damage, etc
 * 
 * AttributeSets are added to the actors as subobjects, and then registered with the AbilitySystemComponent
 * It is often desired to have several sets per project that inherit from each other
 * You could make a base health set, then have a player set that inherits from it and adds more attributes
 */
UCLASS(meta = (DisplayName = "Attribute Set Blueprint Base"))
class BLUEPRINTATTRIBUTES_API UGBAAttributeSetBlueprintBase : public UAttributeSet
{
	GENERATED_BODY()
	REPLICATED_BASE_CLASS(UGBAAttributeSetBlueprintBase)

public:
	explicit UGBAAttributeSetBlueprintBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Serialize(FArchive& Ar) override;

#if WITH_EDITOR
	//~ Begin customization stuff
	/** Ensures CurrentValue for Attributes is kept in sync with BaseValue, when edited from the details panel */
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
	//~ End customization stuff
#endif
	

	//~ Begin UAttributeSet interface

	/**
	 * Initializes attribute data from a meta DataTable.
	 *
	 * The only difference with UAttributeSet::InitFromMetaDataTable() is:
	 *
	 * 1. Filters out trailing "_C" from AttributeSet class names, used when doing a lookup in the datatable.
	 * 2. Adds support for attribute clamping with Min / Max values columns in DataTable
	 */
	virtual void InitFromMetaDataTable(const UDataTable* DataTable) override;

	/**
	 * Called just before modifying the value of an attribute. AttributeSet can make additional modifications here.
	 *
	 * Return true to continue, or false to throw out the modification
	 * 
	 * Note this is only called during an 'execute'. E.g., a modification to the 'base value' of an attribute.
	 * It is not called during an application of a GameplayEffect, such as a 5 second +10 movement speed buff.
	 *
	 * This should apply 'gamewide' rules. Such as clamping Health to MaxHealth or granting +3 health for every point of strength, etc
	 * PreGameplayEffectExecute can return false to 'throw out' this modification.
	 * 
	 * (**Note** When overriding this function in BP, make sure to return true, otherwise the Gameplay Effects won't apply anymore. As the default
	 * behavior for the editor is to implement the method with return value set to false, this is something to be wary off.)
	 *
	 * @param InAttribute The Gameplay Attribute whose value is about to be changed by a Gameplay Effect
	 * @param InData Payload with information extracted from FGameplayEffectModCallbackData, the Source / Target actor, Ability System Component,
	 * Controllers, Effect Context, Specs and Source Tags, Magnitude and Delta values, etc.
	 *
	 * @return Return true to continue, or false to throw out the modification.
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "AttributeSet", DisplayName="PreGameplayEffectExecute")
	bool K2_PreGameplayEffectExecute(const FGameplayAttribute& InAttribute, const FGBAAttributeSetExecutionData& InData);
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;


	/**
	 * Called just after a GameplayEffect is executed to modify the base value of an attribute. No more changes can be made.
	 * 
	 * Note this is only called during an 'execute'. E.g., a modification to the 'base value' of an attribute.
	 * It is not called during an application of a GameplayEffect, such as a 5 second +10 movement speed buff.
	 *
	 * This should apply 'gamewide' rules. Such as clamping Health to MaxHealth or granting +3 health for every point of strength, etc
	 *
	 * @param Attribute The Gameplay Attribute whose value has been changed by a Gameplay Effect
	 * @param Data Payload with information extracted from FGameplayEffectModCallbackData, the Source / Target actor, Ability System Component,
	 * Controllers, Effect Context, Specs and Source Tags, Magnitude and Delta values, etc.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "AttributeSet", DisplayName="PostGameplayEffectExecute")
	void K2_PostGameplayEffectExecute(const FGameplayAttribute& Attribute, const FGBAAttributeSetExecutionData& Data);
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/**
	 * Called just before any modification happens to an attribute. This is lower level than PreAttributeModify/PostAttribute modify.
	 * 
	 * There is no additional context provided here since anything can trigger this.
	 * Executed effects, duration based effects, effects being removed, immunity being applied, stacking rules changing, etc.
	 * 
	 * This function is meant to enforce things like "Health = Clamp(Health, 0, MaxHealth)" and NOT things like
	 * "trigger this extra thing if damage is applied, etc".
	 * 
	 * OutValue is a mutable reference so you are able to clamp the newly applied value as well (**Note** When overriding in BP,
	 * this is the return value of the BP function, make sure to pass in the new value. Typical implementation should simply
	 * return the input value parameter)
	 *
	 * @param InAttribute The Gameplay Attribute whose value is about to change
	 * @param InValue Original value for the Gameplay Attribute
	 * @param OutValue Return value of the function which represents the new value for the Gameplay Attribute
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "AttributeSet", DisplayName="PreAttributeChange")
	void K2_PreAttributeChange(const FGameplayAttribute& InAttribute, float InValue, float& OutValue);
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& OutValue) override;

	/**
	 * Called just after any modification happens to an attribute.
	 * 
	 * @param Attribute The Gameplay Attribute whose value has been changed
	 * @param OldValue Original value for the Gameplay Attribute, before PreAttributeChange event and actual modification happened
	 * @param NewValue New value for the Gameplay Attribute, after PreAttributeChange event and modification
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "AttributeSet", DisplayName="PostAttributeChange")
	void K2_PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue);
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	/**
	 * This is called just before any modification happens to an attribute's base value when an attribute aggregator exists.
	 * This function should enforce clamping (presuming you wish to clamp the base value along with the final value in PreAttributeChange)
	 * This function should NOT invoke gameplay related events or callbacks. Do those in PreAttributeChange() which will be called prior to the
	 * final value of the attribute actually changing.
	 *
	 * @param InAttribute The Gameplay Attribute whose base value is about to change
	 * @param InValue Original value for the Gameplay Attribute
	 * @param OutValue Return value of the function which represents the new base value for the Gameplay Attribute
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "AttributeSet", DisplayName="PreAttributeBaseChange")
	void K2_PreAttributeBaseChange(const FGameplayAttribute& InAttribute, float InValue, float& OutValue) const;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& OutValue) const override;

	/**
	 * Called just after any modification happens to an attribute's base value right after aggregation (when an attribute aggregator exists).
	 * 
	 * @param InAttribute The Gameplay Attribute whose base value has been changed
	 * @param OldValue Original value for the Gameplay Attribute, before PreAttributeBaseChange event and actual modification happened
	 * @param NewValue New value for the Gameplay Attribute, after PreAttributeBaseChange event and modification
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "AttributeSet", DisplayName="PostAttributeBaseChange")
	void K2_PostAttributeBaseChange(const FGameplayAttribute& InAttribute, float OldValue, float NewValue) const;
	virtual void PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const override;

	/** Callback for when an FAggregator is created for an attribute in this set. Allows custom setup of FAggregator::EvaluationMetaData */
	virtual void OnAttributeAggregatorCreated(const FGameplayAttribute& Attribute, FAggregator* NewAggregator) const override;

	/** Print debug information to the log (only called at the end of InitFromMetaDataTable)*/
	virtual void PrintDebug() override;
	//~ End UAttributeSet interface

	/**
	 * Runs clamping logic for a given attribute.
	 *
	 * First clamps if it is a clamped property, then runs clamping via metadata table, if this set was datatable
	 * initialized and has a corresponding row name.
	 *
	 * @param InAttribute Attribute to base the clamping calculation upon
	 * @param OutValue Return value for the attribute if clamped was performed
	 * 
	 * @returns true whether clamping was done and OutValue was changed
	 */
	bool PerformClampingForAttribute(const FGameplayAttribute& InAttribute, float& OutValue);

	/**
	 * Clamps the Attribute from MinValue to MaxValue
	 *
	 * @param Attribute Gameplay Attribute to clamp the value
	 * @param MinValue The lower bound float to clamp the value within
	 * @param MaxValue The higher bound float to clamp the value within
	 */
	UFUNCTION(BlueprintCallable, Category = "Blueprint Attributes")
	virtual void ClampAttributeValue(const FGameplayAttribute Attribute, float MinValue, float MaxValue);

	// Note: const FGameplayAttribute& vs FGameplayAttribute for BlueprintCallables
	// Using param without const ref is preferable in BP due to having the Dropdown for the graph pin

	/**
	 * Returns the *current* (as opposed to base) value of an Attribute.
	 *
	 * @param Attribute The Gameplay Attribute we want to get the current value
	 * @param bSuccessfullyFoundAttribute Return value indicating whether the value was retrieved successfully
	 * (false if owning ASC is invalid or if the AttributeSet the input Attribute belong to is not granted)
	 *
	 * @return Current Value for the Gameplay Attribute
	 */
	UFUNCTION(BlueprintPure, Category = "Blueprint Attributes", DisplayName="GetAttributeValue")
	float K2_GetAttributeValue(FGameplayAttribute Attribute, bool& bSuccessfullyFoundAttribute) const;
	float GetAttributeValue(const FGameplayAttribute& Attribute, bool& bSuccessfullyFoundAttribute) const;

	/**
	 * Returns the *base* (as opposed to current) value of an Attribute.
	 *
	 * @param Attribute The Gameplay Attribute we want to get the base value
	 * @param bSuccessfullyFoundAttribute Return value indicating whether the value was retrieved successfully
	 * (false if owning ASC is invalid or if the AttributeSet the input Attribute belong to is not granted)
	 *
	 * @return Base Value for the Gameplay Attribute
	 */
	UFUNCTION(BlueprintPure, Category = "Blueprint Attributes", DisplayName="GetAttributeBaseValue")
	float K2_GetAttributeBaseValue(FGameplayAttribute Attribute, bool& bSuccessfullyFoundAttribute) const;
	float GetAttributeBaseValue(const FGameplayAttribute& Attribute, bool& bSuccessfullyFoundAttribute) const;

	/**
	 * Sets the *base* (as opposed to current) value of an Attribute.
	 *
	 * @param Attribute The Gameplay Attribute we want to set the base value
	 * @param NewValue Float value to set
	 */
	UFUNCTION(BlueprintCallable, Category = "Blueprint Attributes", DisplayName="SetAttributeValue")
	void K2_SetAttributeValue(FGameplayAttribute Attribute, float NewValue);
	void SetAttributeValue(const FGameplayAttribute& Attribute, float NewValue) const;

	/** Returns true if the variable associated with Property is of type FGBAGameplayClampedAttributeData or one of its subclasses */
	static bool IsGameplayAttributeDataClampedProperty(const FProperty* Property);

	/** Gets information about owning actor */
	UFUNCTION(BlueprintCallable, Category = "Blueprint Attributes", DisplayName="GetOwningActor")
	AActor* K2_GetOwningActor() const;

	/** Returns the Ability System Component of the Owning Actor */
	UFUNCTION(BlueprintCallable, Category = "Blueprint Attributes", DisplayName="GetOwningAbilitySystemComponent")
	UAbilitySystemComponent* K2_GetOwningAbilitySystemComponent() const;

	/**
	 * Returns the Owner's Ability System Component cached data about the owning actor that abilities will need to frequently access
	 * (movement component, mesh component, anim instance, etc)
	 */
	UFUNCTION(BlueprintCallable, Category = "Blueprint Attributes", DisplayName="GetActorInfo")
	FGameplayAbilityActorInfo K2_GetActorInfo() const;

	/** Internal implementation of Blueprint rep notifies GAMEPLAYATTRIBUTE_REPNOTIFY equivalent */
	void HandleRepNotifyForGameplayAttribute(FName InPropertyName);
	
	/**
	 * To be called from Blueprint rep notifies for a given Gameplay Attribute Data member variable.
	 *
	 * Meant to provide the same prediction capabilities of GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Attribute, OldAttribute) macro that is usually
	 * called from within a C++ AttributeSet rep notify handler.
	 *
	 * @param InAttribute The Gameplay Attribute Data property to handle rep notify for. Simply wire in the appropriate
	 * Blueprint member Attribute variable for the rep notify you're implementing.
	 */
	UFUNCTION(BlueprintCallable, Category = "Blueprint Attributes")
	void HandleRepNotifyForGameplayAttributeData(const FGameplayAttributeData& InAttribute);
	
	/**
	 * To be called from Blueprint rep notifies for a given (Clamped) Gameplay Attribute Data member variable.
	 *
	 * Meant to provide the same prediction capabilities of GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Attribute, OldAttribute) macro that is usually
	 * called from within a C++ AttributeSet rep notify handler.
	 * 
	 * @param InAttribute The Gameplay Attribute Data property to handle rep notify for. Simply wire in the appropriate
	 * Blueprint member Attribute variable for the rep notify you're implementing.
	 */
	UFUNCTION(BlueprintCallable, Category = "Blueprint Attributes")
	void HandleRepNotifyForGameplayClampedAttributeData(const FGBAGameplayClampedAttributeData& InAttribute);

	//~ Begin UObject interface
	virtual void BeginDestroy() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreNetReceive() override;
	
#if WITH_EDITOR
#if UE_VERSION_NEWER_THAN(5, 3, -1)
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#else
	virtual EDataValidationResult IsDataValid(TArray<FText>& ValidationErrors) override;
#endif
	
	//~ End UObject interface

	/**
	 * Called from IsDataValid(), performs validation of the current Blueprint, checking it is using the correct Blueprint Editor.
	 *
	 * Returns invalid if it is not, which raises a compiler warning (via IsDataValid())
	 */
	EDataValidationResult IsDataValidBlueprintEditor(TArray<FText>& ValidationErrors) const;

	/**
	 * Implements validation rules run in IsDataValid, specifically for replicated properties.
	 *
	 * Checks:
	 *
	 * 1. Checks all attribute replicated props are using RepNotify
	 * 2. Checks all attribute replicated are implementing the corresponding rep notify function
	 * 3. Checks all rep notify function for an attribute are using HandleRepNotifyForGameplayAttribute(),
	 * is wired in to the execution pin, and is using the correct FGameplayAttributeData property for its
	 * parameter (name of the rep notified and the InAttribute property should match)
	 */
	EDataValidationResult IsDataValidRepNotifies(TArray<FText>& ValidationErrors) const;
	static bool IsNodeWiredToEntry(const UK2Node* InNode);

	static UEdGraphPin* FindGraphNodePin(const UEdGraphNode* InNode, const EEdGraphPinDirection InDirection);
#endif

	/** Getter to return current state of AttributesMetaData map */
	TMap<FString, TSharedPtr<FAttributeMetaData>> GetAttributesMetaData() const;

protected:
	/** Stores cached values of FGameplayAttributeData during a PostNetReceive() for use later on within rep notifies */
	TMap<FString, TSharedPtr<FGameplayAttributeData>> AttributeDataRepMap;

	/** Stores cached values of FAttributeMetaData that was read from an initialization data table during InitFromMetaDataTable() */
	TMap<FString, TSharedPtr<FAttributeMetaData>> AttributesMetaData;

	/** List of valid rep notify handler for GameplayAttributes (HandleRepNotify...). Key is the CPP type, Value is the function name. */
	static TMap<FString, FString> RepNotifierHandlerNames;
	
	/**
	 * Called during construction from InitFromMetaDataTable(), this ensures FGBAGameplayClampedAttributeData clamps
	 * their BaseValue within the defined bounds, as doing so from InitFromMetaDataTable can be skipped (if InitStats
	 * not called, if called with a nullptr DataTable, etc.)
	 */
	void InitClampedAttributeDataProperties();

	/** Called during construction from InitFromMetaDataTable() */
	void InitDataTableProperties(const UDataTable* DataTable);
	
	/** Returns whether given Attribute is defined using a FGBAGameplayClampedAttributeData property, and if it has valid clamping values */
	bool IsValidClampedProperty(const FGameplayAttribute& Attribute);

	/** Returns the new value for an attribute after clamping via FGBAGameplayClampedAttributeData defaults Min / Max values */
	float GetClampedValueForClampedProperty(const FGameplayAttribute& Attribute, float InValue);
	
	/** Returns whether given Attribute metadata has valid clamping values */
	static bool IsValidAttributeMetadata(const FAttributeMetaData& InAttributeMetadata);
	
	/** Returns whether given Attribute metadata has valid clamping values */
	static bool IsValidAttributeMetadata(const TSharedPtr<FAttributeMetaData>& InAttributeMetadata);

	/** Returns whether given Attribute has stored MetaData, and if it has valid clamping values */
	bool HasClampedMetaData(const FGameplayAttribute& Attribute);

	/** Returns the new value for an attribute after clamping via stored MetaData (from DataTable) */
	float GetClampedValueForMetaData(const FGameplayAttribute& Attribute, float InValue);

	/** Returns all Blueprint member variables marked as replicated for this class */
	void GetAllBlueprintReplicatedProps(TArray<FProperty*>& OutProperties, EPropertyFlags InCheckFlag = CPF_Net) const;

	/**
	 * Equivalent of UBlueprintGeneratedClass::GetLifetimeBlueprintReplicationList() but returns a list of FProperty instead.
	 *
	 * Iterates through all Blueprint member variables that are marked to replicate, for the direct passed in UClass and all its Blueprint parent, until
	 * no parent Blueprint is found.
	 */
	void GetAllBlueprintReplicatedProps(UClass* InClass, TArray<FProperty*>& OutProperties, EPropertyFlags InCheckFlag = CPF_Net) const;
	
	/** Returns the property name of a given FGameplayAttributeData (or one of its child struct) */
	bool GetAttributeDataPropertyName(const FGameplayAttributeData& InAttributeData, FString& OutPropertyName);
};
