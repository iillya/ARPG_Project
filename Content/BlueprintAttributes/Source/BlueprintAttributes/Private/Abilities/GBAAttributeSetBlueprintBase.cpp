// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "Abilities/GBAAttributeSetBlueprintBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GBAConstants.h"
#include "GBALog.h"
#include "GameplayEffectExtension.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "GameFramework/PlayerController.h"
#include "Misc/EngineVersionComparison.h"
#include "UObject/UnrealType.h"
#include "Utils/GBAUtils.h"

#if UE_VERSION_NEWER_THAN(5, 3, -1)
#include "Misc/DataValidation.h"
#endif

#if WITH_EDITOR
#include "Editor.h"
#include "K2Node_CallFunction.h"
#include "K2Node_FunctionEntry.h"
#include "K2Node_VariableGet.h"
#include "EdGraph/EdGraph.h"
#include "Subsystems/AssetEditorSubsystem.h"
#endif

#define LOCTEXT_NAMESPACE "UGBAAttributeSetBlueprintBase"

TMap<FString, FString> UGBAAttributeSetBlueprintBase::RepNotifierHandlerNames = {
	{ TEXT("FGameplayAttributeData"), TEXT("HandleRepNotifyForGameplayAttributeData") },
	{ TEXT("FGBAGameplayClampedAttributeData"), TEXT("HandleRepNotifyForGameplayClampedAttributeData") }
};

FGBAAttributeSetExecutionData::FGBAAttributeSetExecutionData(const FGameplayEffectModCallbackData& InModCallbackData)
{
	Context = InModCallbackData.EffectSpec.GetContext();
	SourceASC = Context.GetOriginalInstigatorAbilitySystemComponent();
	TargetASC = &InModCallbackData.Target;
	SourceTags = *InModCallbackData.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	InModCallbackData.EffectSpec.GetAllAssetTags(SpecAssetTags);

	const TSharedPtr<FGameplayAbilityActorInfo> TargetActorInfo = InModCallbackData.Target.AbilityActorInfo;
	const TSharedPtr<FGameplayAbilityActorInfo> SourceActorInfo = SourceASC ? SourceASC->AbilityActorInfo : nullptr;

	if (TargetActorInfo.IsValid())
	{
		TargetActor = TargetActorInfo->AvatarActor.Get();
		TargetController = TargetActorInfo->PlayerController.Get();
	}

	// Set the source actor based on context if it's set
	if (Context.GetEffectCauser())
	{
		SourceActor = Context.GetEffectCauser();
	}
	else if (SourceActorInfo.IsValid())
	{
		SourceActor = SourceActorInfo->AvatarActor.Get();
	}

	if (SourceActorInfo.IsValid())
	{
		SourceController = SourceActorInfo->PlayerController.Get();
	}

	SourceObject = InModCallbackData.EffectSpec.GetEffectContext().GetSourceObject();

	// Compute the delta between old and new, if it is available
	MagnitudeValue = InModCallbackData.EvaluatedData.Magnitude;

	if (InModCallbackData.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		// If this was additive, store the raw delta value to be passed along later
		DeltaValue = InModCallbackData.EvaluatedData.Magnitude;
	}
}

FString FGBAAttributeSetExecutionData::ToString(const FString& InSeparator) const
{
	const TArray Results = {
		FString::Printf(TEXT("SourceActor: %s"), *GetNameSafe(SourceActor)),
		FString::Printf(TEXT("TargetActor: %s"), *GetNameSafe(TargetActor)),
		FString::Printf(TEXT("SourceASC: %s"), *GetNameSafe(SourceASC)),
		FString::Printf(TEXT("TargetASC: %s"), *GetNameSafe(TargetASC)),
		FString::Printf(TEXT("SourceController: %s"), *GetNameSafe(SourceController)),
		FString::Printf(TEXT("TargetController: %s"), *GetNameSafe(TargetController)),
		FString::Printf(TEXT("SourceObject: %s"), *GetNameSafe(SourceObject)),
		FString::Printf(TEXT("SourceTags: %s"), *SourceTags.ToString()),
		FString::Printf(TEXT("SpecAssetTags: %s"), *SpecAssetTags.ToString()),
	};

	return FString::Join(Results, *InSeparator);
}

float FGBAClampDefinition::GetValueForClamping(const UAttributeSet* InOwnerSet) const
{
	check(InOwnerSet);

	float ResultValue;
	GetValueForClamping(InOwnerSet, ResultValue);

	return ResultValue;
}

bool FGBAClampDefinition::GetValueForClamping(const UAttributeSet* InOwnerSet, float& OutValue) const
{
	check(InOwnerSet);

	if (ClampType == EGBAClampingType::None)
	{
		OutValue = 0.f;
		return false;
	}
	
	if (ClampType == EGBAClampingType::Float)
	{
		OutValue = Value;
		return true;
	}

	if (ClampType == EGBAClampingType::AttributeBased && Attribute.IsValid())
	{
		// Check if valid class (eg. attribute is part of InOwnerSet and not from another set)
		if (const FProperty* Property = Attribute.GetUProperty())
		{
			const UStruct* OwnerStruct = Property->GetOwnerStruct();
			if (!InOwnerSet->GetClass()->IsChildOf(OwnerStruct))
			{
				GBA_LOG(
					Warning,
					TEXT("FGBAClampDefinition::GetValueForClamping - Unable to get attribute value for %s because it's not a member of %s"),
					*Attribute.GetName(),
					*GetNameSafe(InOwnerSet)
				)
				OutValue = 0.f;
				return false;
			}
		}
		
		const FGameplayAttributeData* AttributeData = Attribute.GetGameplayAttributeData(InOwnerSet);
		if (!AttributeData)
		{
			GBA_LOG(
				Warning,
				TEXT("FGBAClampDefinition::GetValueForClamping - Unable to get attribute value for %s because attribute failed to return its attribute data"),
				*Attribute.GetName()
			)
			GBA_LOG(Warning, TEXT("\t Is %s attribute a member of Attribute Set %s ?"), *Attribute.GetName(), *GetNameSafe(InOwnerSet))
			OutValue = 0.f;
			return false;
		}

		OutValue = AttributeData->GetCurrentValue();
		return true;
	}

	return false;
}

UGBAAttributeSetBlueprintBase::UGBAAttributeSetBlueprintBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UGBAAttributeSetBlueprintBase::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
		FGBAUtils::SerializeAttributeSet(this, Ar);
	}
}

#if WITH_EDITOR
void UGBAAttributeSetBlueprintBase::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	if (!PropertyChangedEvent.MemberProperty)
	{
		return;
	}

	const FName PropertyChangedName = PropertyChangedEvent.MemberProperty->GetFName();
	const UStruct* OwnerStruct = PropertyChangedEvent.MemberProperty->GetOwnerStruct();
	
	// protected visibility on BaseValue prevents us from using GET_MEMBER_NAME_CHECKED(FGameplayAttributeData, BaseValue);
	if (OwnerStruct != FGameplayAttributeData::StaticStruct() || PropertyChangedName != GBA::Constants::BaseValuePropertyName)
	{
		return;
	}
	
	const FEditPropertyChain::TDoubleLinkedListNode* MemberNode = PropertyChangedEvent.PropertyChain.GetActiveMemberNode();
	if (!MemberNode)
	{
		return;
	}

	const FProperty* MemberProperty = MemberNode->GetValue();
	if (FGameplayAttribute::IsGameplayAttributeDataProperty(MemberProperty))
	{
		FGameplayAttributeData* DataPtr = MemberProperty->ContainerPtrToValuePtr<FGameplayAttributeData>(this);
		check(DataPtr);

		const float BaseValue = DataPtr->GetBaseValue();
		DataPtr->SetCurrentValue(BaseValue);
	}
}
#endif

void UGBAAttributeSetBlueprintBase::InitFromMetaDataTable(const UDataTable* DataTable)
{
	GBA_NS_LOG(Verbose, TEXT("DataTable: %s"), *GetNameSafe(DataTable))
	
	// Deal with metadata table
	InitDataTableProperties(DataTable);
	
	// Then with clamped properties
	//
	// Although this won't run if InitStats (and consequently InitFromMetaDataTable) is not used, or if InitStats() /
	// DefaultStartingData is used with a nullptr DataTable, or granting is done without calling InitFromMetaDataTable.
	InitClampedAttributeDataProperties();
	
	PrintDebug();
}

bool UGBAAttributeSetBlueprintBase::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	const bool bShouldExecute = Super::PreGameplayEffectExecute(Data);
	return bShouldExecute && K2_PreGameplayEffectExecute(Data.EvaluatedData.Attribute, FGBAAttributeSetExecutionData(Data));
}

bool UGBAAttributeSetBlueprintBase::K2_PreGameplayEffectExecute_Implementation(const FGameplayAttribute& InAttribute, const FGBAAttributeSetExecutionData& InData)
{
	return true;
}

void UGBAAttributeSetBlueprintBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGBAAttributeSetExecutionData ExecutionData(Data);

	// Call BP event if implemented
	K2_PostGameplayEffectExecute(Data.EvaluatedData.Attribute, ExecutionData);

	// Run before or after BP implementation ?
	// Or don't run built-in clamping if K2_PostGameplayEffectExecute implemented in BP ?
	
	bool bSuccessfullyFoundAttribute = true;
	float NewValue = GetAttributeValue(Data.EvaluatedData.Attribute, bSuccessfullyFoundAttribute);
	if (!bSuccessfullyFoundAttribute)
	{
		GBA_LOG(
			Warning,
			TEXT("UGBAAttributeSetBlueprintBase::PostGameplayEffectExecute - Error reading %s value (clamping if any was expected couldn't be performed)"),
			*Data.EvaluatedData.Attribute.GetName()
		)
		return;
	}
	
	const bool bWasClamped = PerformClampingForAttribute(Data.EvaluatedData.Attribute, NewValue);
	if (bWasClamped)
	{
		SetAttributeValue(Data.EvaluatedData.Attribute, NewValue);
	}
}

void UGBAAttributeSetBlueprintBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& OutValue)
{
	Super::PreAttributeChange(Attribute, OutValue);

	// Pass in an additional float param to the BP event, reference value are handled differently in BP and far less intuitive than in native
	const float Value = OutValue;
	K2_PreAttributeChange(Attribute, Value, OutValue);

	// Run before or after BP implementation ?
	// Or don't run built-in clamping if K2_PreAttributeChange implemented in BP ?
	PerformClampingForAttribute(Attribute, OutValue);
}

void UGBAAttributeSetBlueprintBase::PostAttributeChange(const FGameplayAttribute& Attribute, const float OldValue, const float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	K2_PostAttributeChange(Attribute, OldValue, NewValue);
}

void UGBAAttributeSetBlueprintBase::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& OutValue) const
{
	Super::PreAttributeBaseChange(Attribute, OutValue);

	// Pass in an additional float param to the BP event, reference value are handled differently in BP and far less intuitive than in native
	const float Value = OutValue;
	K2_PreAttributeBaseChange(Attribute, Value, OutValue);
}

void UGBAAttributeSetBlueprintBase::PostAttributeBaseChange(const FGameplayAttribute& Attribute, const float OldValue, const float NewValue) const
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
	K2_PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

void UGBAAttributeSetBlueprintBase::OnAttributeAggregatorCreated(const FGameplayAttribute& Attribute, FAggregator* NewAggregator) const
{
	Super::OnAttributeAggregatorCreated(Attribute, NewAggregator);

	// TO DO: Would likely need a wrapper USTRUCT exposed to BP to FAggregator
	// With things like SetEvaluationMetaData
	// to expose this event to BP
}

void UGBAAttributeSetBlueprintBase::PrintDebug()
{
	Super::PrintDebug();
}

bool UGBAAttributeSetBlueprintBase::PerformClampingForAttribute(const FGameplayAttribute& InAttribute, float& OutValue)
{
	float NewValue = OutValue;
	bool bWasClamped = false;

	// First attempt clamp if it is a clamped property
	if (IsValidClampedProperty(InAttribute))
	{
		NewValue = GetClampedValueForClampedProperty(InAttribute, NewValue);
		bWasClamped = true;
	}
	
	// Then runs clamping via metadata table, if this set was datatable initialized and has a corresponding row name
	if (HasClampedMetaData(InAttribute))
	{
		NewValue = GetClampedValueForMetaData(InAttribute, NewValue);
		bWasClamped = true;
	}
	
	if (bWasClamped)
	{
		OutValue = NewValue;
	}

	return bWasClamped;
}

void UGBAAttributeSetBlueprintBase::ClampAttributeValue(const FGameplayAttribute Attribute, const float MinValue, const float MaxValue)
{
	bool bSuccessfullyFoundAttribute = true;
	const float CurrentValue = GetAttributeValue(Attribute, bSuccessfullyFoundAttribute);
	if (!bSuccessfullyFoundAttribute)
	{
		GBA_LOG(
			Warning,
			TEXT("UGBAAttributeSetBlueprintBase::ClampAttributeValue - Error reading %s value (clamping couldn't be performed)"),
			*Attribute.GetName()
		)
		return;
	}
	
	const float NewValue = FMath::Clamp(CurrentValue, MinValue, MaxValue);

	GBA_NS_LOG(
		Verbose,
		TEXT("Clamping attribute %s value to %f (was %f) from Min: %f - Max: %f"),
		*Attribute.GetName(),
		NewValue,
		CurrentValue,
		MinValue,
		MaxValue
	)

	SetAttributeValue(Attribute, NewValue);
}

float UGBAAttributeSetBlueprintBase::K2_GetAttributeValue(FGameplayAttribute Attribute, bool& bSuccessfullyFoundAttribute) const
{
	return GetAttributeValue(Attribute, bSuccessfullyFoundAttribute);
}

float UGBAAttributeSetBlueprintBase::GetAttributeValue(const FGameplayAttribute& Attribute, bool& bSuccessfullyFoundAttribute) const
{
	const UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	if (!ASC)
	{
		GBA_LOG(Warning, TEXT("UGBAAttributeSetBlueprintBase::GetAttributeValue - Unable to get attribute value for %s because ASC is invalid"), *Attribute.GetName())
		bSuccessfullyFoundAttribute = false;
		return 0.f;
	}

	return UAbilitySystemBlueprintLibrary::GetFloatAttributeFromAbilitySystemComponent(ASC, Attribute, bSuccessfullyFoundAttribute);
}

float UGBAAttributeSetBlueprintBase::K2_GetAttributeBaseValue(FGameplayAttribute Attribute, bool& bSuccessfullyFoundAttribute) const
{
	return GetAttributeBaseValue(Attribute, bSuccessfullyFoundAttribute);
}

float UGBAAttributeSetBlueprintBase::GetAttributeBaseValue(const FGameplayAttribute& Attribute, bool& bSuccessfullyFoundAttribute) const
{
	const UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	if (!ASC)
	{
		GBA_LOG(Warning, TEXT("UGBAAttributeSetBlueprintBase::GetAttributeBaseValue - Unable to get attribute value for %s because ASC is invalid"), *Attribute.GetName())
		bSuccessfullyFoundAttribute = false;
		return 0.f;
	}

	return UAbilitySystemBlueprintLibrary::GetFloatAttributeBaseFromAbilitySystemComponent(ASC, Attribute, bSuccessfullyFoundAttribute);
}

// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeConst
void UGBAAttributeSetBlueprintBase::K2_SetAttributeValue(const FGameplayAttribute Attribute, const float NewValue)
{
	SetAttributeValue(Attribute, NewValue);
}

void UGBAAttributeSetBlueprintBase::SetAttributeValue(const FGameplayAttribute& Attribute, const float NewValue) const
{
	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	if (!ASC)
	{
		GBA_LOG(Warning, TEXT("UGBAAttributeSetBlueprintBase::SetAttributeValue - Unable to set value for %s because ASC is invalid"), *Attribute.GetName())
		return;
	}

	ASC->SetNumericAttributeBase(Attribute, NewValue);
}

bool UGBAAttributeSetBlueprintBase::IsGameplayAttributeDataClampedProperty(const FProperty* Property)
{
	if (const FStructProperty* StructProp = CastField<FStructProperty>(Property))
	{
		const UStruct* Struct = StructProp->Struct;
		if (Struct && Struct->IsChildOf(FGBAGameplayClampedAttributeData::StaticStruct()))
		{
			return true;
		}
	}

	return false;
}

AActor* UGBAAttributeSetBlueprintBase::K2_GetOwningActor() const
{
	return GetOwningActor();
}

UAbilitySystemComponent* UGBAAttributeSetBlueprintBase::K2_GetOwningAbilitySystemComponent() const
{
	return GetOwningAbilitySystemComponent();
}

FGameplayAbilityActorInfo UGBAAttributeSetBlueprintBase::K2_GetActorInfo() const
{
	FGameplayAbilityActorInfo* ActorInfo = GetActorInfo();
	if (!ActorInfo)
	{
		GBA_LOG(Error, TEXT("UGBAAttributeSetBlueprintBase::K2_GetActorInfo - Unable to get actor info pointer"))
		return FGameplayAbilityActorInfo();
	}

	return *ActorInfo;
}

void UGBAAttributeSetBlueprintBase::HandleRepNotifyForGameplayAttribute(const FName InPropertyName)
{
	FProperty* ThisProperty = FindFProperty<FProperty>(GetClass(), InPropertyName);
	
	if (!ThisProperty)
	{
		GBA_LOG(
			Warning,
			TEXT("UGBAAttributeSetBlueprintBase::HandleRepNotifyForGameplayAttribute - Invalid InPropertyName (%s) - could not find in %s"),
			*InPropertyName.ToString(),
			*GetNameSafe(GetClass())
		)
		return;
	}
	
	const FGameplayAttribute Attribute = FGameplayAttribute(ThisProperty);
	const FGameplayAttributeData* AttributeData = Attribute.GetGameplayAttributeData(this);
	{
		const FString ErrorMessage = FString::Printf(TEXT("Was unable to determine current attribute data for property: %s"), *InPropertyName.ToString());
		if (!ensureMsgf(AttributeData, TEXT("%s"), *ErrorMessage))
		{
			GBA_LOG(Error, TEXT("UGBAAttributeSetBlueprintBase::HandleRepNotifyForGameplayAttribute - %s"), *ErrorMessage)
			return;
		}
	}

	// Try to find old attribute data from pre-computed rep map in PreNetReceive, that should contain the value right before receiving the net update
	const FString Key = FString::Printf(TEXT("%s.%s"), *GetNameSafe(ThisProperty->GetOwnerClass()), *InPropertyName.ToString());

	const FGameplayAttributeData* OldAttributeDataPtr = AttributeDataRepMap.Contains(Key) ? AttributeDataRepMap.FindChecked(Key).Get() : nullptr;
	{
		const FString ErrorMessage = FString::Printf(TEXT("Was unable to determine old attribute data for property: %s"), *InPropertyName.ToString());
		if (!ensureMsgf(OldAttributeDataPtr, TEXT("%s"), *ErrorMessage))
		{
			GBA_LOG(Error, TEXT("UGBAAttributeSetBlueprintBase::HandleRepNotifyForGameplayAttribute - %s"), *ErrorMessage)
		}
	}

	const FGameplayAttributeData OldAttributeData = OldAttributeDataPtr != nullptr ? *OldAttributeDataPtr : FGameplayAttributeData();
	GetOwningAbilitySystemComponent()->SetBaseAttributeValueFromReplication(Attribute, *AttributeData, OldAttributeData);
}

void UGBAAttributeSetBlueprintBase::HandleRepNotifyForGameplayAttributeData(const FGameplayAttributeData& InAttribute)
{
	FString AttributeName;
	if (!GetAttributeDataPropertyName(InAttribute, AttributeName))
	{
		const FString ErrorMessage = FString::Printf(
			TEXT(
				"Unable to determine AttributeName - AttribtueSet: %s - "
				"This shouldn't happen and will prevent proper predictive attribute replication handling."
			),
			*GetName()
		);
		
		ensureMsgf(false, TEXT("%s"), *ErrorMessage);
		GBA_NS_LOG(Warning, TEXT("%s"), *ErrorMessage);
		return;
	}

	HandleRepNotifyForGameplayAttribute(FName(*AttributeName));
}

void UGBAAttributeSetBlueprintBase::HandleRepNotifyForGameplayClampedAttributeData(const FGBAGameplayClampedAttributeData& InAttribute)
{
	HandleRepNotifyForGameplayAttributeData(InAttribute);
}

void UGBAAttributeSetBlueprintBase::BeginDestroy()
{
	AttributesMetaData.Empty();
	AttributeDataRepMap.Empty();
	Super::BeginDestroy();
}

void UGBAAttributeSetBlueprintBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	const UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(GetClass());
	if (BPClass != nullptr)
	{
		BPClass->GetLifetimeBlueprintReplicationList(OutLifetimeProps);
	}
}

void UGBAAttributeSetBlueprintBase::PreNetReceive()
{
	Super::PreNetReceive();
	
	// During the scope of this entire actor's network update, we need to track down attributes and store their value, just before receiving a network update
	// Used to build a map of attribute data in PreNetReceive (just before receiving a bunch), that is later used in HandleRepNotifyForGameplayAttribute()
	// (meant to be called from a BP repnotify) to retrieve the old attribute data and pass it down to ASC SetBaseAttributeValueFromReplication(),
	// just like it would be done via a regular C++ repnotify and GAMEPLAYATTRIBUTE_REPNOTIFY macro.
	//
	// All of this is necessary because of BP rep notifies not accepting a param (to represent the old state) as we can do in cpp

	TArray<FProperty*> ReplicatedProps;
	GetAllBlueprintReplicatedProps(ReplicatedProps);

	AttributeDataRepMap.Reset();
	AttributeDataRepMap.Reserve(ReplicatedProps.Num());

	GBA_LOG(VeryVerbose, TEXT("UGBAAttributeSetBlueprintBase::PreNetReceive ... ReplicatedProps: %d"), ReplicatedProps.Num())
	for (FProperty* Prop : ReplicatedProps)
	{
		if (!Prop || !Prop->GetOwnerClass())
		{
			continue;
		}

		const FGameplayAttribute Attribute = FGameplayAttribute(Prop);
		const FGameplayAttributeData* AttributeData = Attribute.GetGameplayAttributeData(this);
		if (!ensureMsgf(AttributeData, TEXT("Could not get attribute data from property: %s"), *GetNameSafe(Prop)))
		{
			continue;
		}
		
		GBA_LOG(VeryVerbose, TEXT("\t Prop: %s (Owner: %s) - Value: %f"), *GetNameSafe(Prop), *GetNameSafe(Prop->GetOwnerClass()), AttributeData->GetCurrentValue())
		if (const UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent())
		{
			GBA_LOG(VeryVerbose, TEXT("\t\t Prop: %s (Owner: %s) - ASC Value: %f"), *GetNameSafe(Prop), *GetNameSafe(Prop->GetOwnerClass()), ASC->GetNumericAttribute(Attribute))
		}

		FString Key = FString::Printf(TEXT("%s.%s"), *Prop->GetOwnerClass()->GetName(), *Prop->GetName());
		AttributeDataRepMap.Add(Key, MakeShared<FGameplayAttributeData>(*AttributeData));
	}
}

#if WITH_EDITOR

#if UE_VERSION_NEWER_THAN(5, 3, -1)

EDataValidationResult UGBAAttributeSetBlueprintBase::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

	{
		TArray<FText> ValidationErrors;
		Result = CombineDataValidationResults(Result, IsDataValidBlueprintEditor(ValidationErrors));

		// Add to context manually until IsDataValidBlueprintEditor is re-written to work off FDataValidationContext in 5.6 (IsDataValid() with array of errors deprecated in 5.3)
		for (const FText& ValidationError : ValidationErrors)
		{
			Context.AddError(ValidationError);
		}
	}

	{
		
		TArray<FText> ValidationErrors;
		Result = CombineDataValidationResults(Result, IsDataValidRepNotifies(ValidationErrors));
		
		// Add to context manually until IsDataValidBlueprintEditor is re-written to work off FDataValidationContext in 5.6 (IsDataValid() with array of errors deprecated in 5.3)
		for (const FText& ValidationError : ValidationErrors)
		{
			Context.AddError(ValidationError);
		}
	}
	
	return Result;
}

#else

EDataValidationResult UGBAAttributeSetBlueprintBase::IsDataValid(TArray<FText>& ValidationErrors)
{
	EDataValidationResult Result = CombineDataValidationResults(Super::IsDataValid(ValidationErrors), EDataValidationResult::Valid);
	Result = CombineDataValidationResults(Result, IsDataValidBlueprintEditor(ValidationErrors));
	Result = CombineDataValidationResults(Result, IsDataValidRepNotifies(ValidationErrors));
	return Result;
}

#endif

EDataValidationResult UGBAAttributeSetBlueprintBase::IsDataValidBlueprintEditor(TArray<FText>& ValidationErrors) const
{
	EDataValidationResult Result = EDataValidationResult::NotValidated;
	
	if (!GEditor)
	{
		return Result;
	}

	const UPackage* Package = GetPackage();
	if (!Package)
	{
		return Result;
	}

	UObject* TestObject = StaticLoadObject(UObject::StaticClass(), nullptr, *Package->GetFName().ToString());
	if (!TestObject)
	{
		return Result;
	}

	UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
	const IAssetEditorInstance* EditorInstance = AssetEditorSubsystem->FindEditorForAsset(TestObject, false);
	if (!EditorInstance)
	{
		return Result;
	}

	const FString EditorName = EditorInstance->GetEditorName().ToString();
	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprintBase::IsDataValid TestObject: %s"), *GetNameSafe(TestObject))
	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprintBase::IsDataValid EditorName: %s"), *EditorName)

	// TODO: Have FGBABlueprintEditor::GetToolkitFName use a constant defined somewhere
	if (EditorName != TEXT("GBABlueprintEditor"))
	{
		Result = EDataValidationResult::Invalid;
		const FText ErrorText = FText::Format(
			LOCTEXT(
				"Invalid_Editor",
				"Seems like {0} is not using the correct editor (Expected: GBABlueprintEditor, Current: {1}). "
				"The blueprint should be created from context menu using the provided factory."
			),
			FText::FromString(GetName()),
			FText::FromString(EditorName)
		);
		ValidationErrors.Add(ErrorText);
		ValidationErrors.Add(LOCTEXT(
			"Invalid_Editor_Description",
			"You'll be missing key features and can experience crashes when renaming Attribute properties while having Gameplay Effect Blueprints opened if they are referencing them."
		));
	}

	return Result;
}

EDataValidationResult UGBAAttributeSetBlueprintBase::IsDataValidRepNotifies(TArray<FText>& ValidationErrors) const
{
	EDataValidationResult Result = EDataValidationResult::NotValidated;

	TArray<FProperty*> ReplicatedProperties;
	GetAllBlueprintReplicatedProps(ReplicatedProperties);

	GBA_LOG(VeryVerbose, TEXT("UGBAAttributeSetBlueprintBase::IsDataValidRepNotifies - Check for rep notifies validity ..."))
	
	const UBlueprint* Blueprint = UBlueprint::GetBlueprintFromClass(GetClass());
	GBA_LOG(VeryVerbose, TEXT("UGBAAttributeSetBlueprintBase::IsDataValidRepNotifies - Blueprint: %s"), *GetNameSafe(Blueprint))
	if (!Blueprint)
	{
		return Result;
	}

	TArray<FProperty*> RepNotifiedProperties;
	
	// First pass, check all replicated props are using RepNotify
	GBA_LOG(VeryVerbose, TEXT("UGBAAttributeSetBlueprintBase::IsDataValidRepNotifies - ReplicatedProperties: %d"), ReplicatedProperties.Num())
	for (FProperty* Property : ReplicatedProperties)
	{
		if (!Property)
		{
			continue;
		}
		
		const bool bIsRepNotified = Property->HasAllPropertyFlags(CPF_RepNotify);
		GBA_LOG(VeryVerbose, TEXT("\t Property: %s (bIsRepNotified: %s)"), *GetNameSafe(Property), bIsRepNotified ? TEXT("true") : TEXT("false"))
		if (!bIsRepNotified)
		{
			Result = EDataValidationResult::Invalid;
			ValidationErrors.Add(FText::Format(
				LOCTEXT("Invalid_Replicated", "Property {0} is replicated but no rep notify function could be found. Please use RepNotify instead in the Replication dropdown."),
				FText::FromString(Property->GetName())
			));
			
			continue;
		}

		RepNotifiedProperties.Add(Property);
	}
	
	// Second pass, check all rep notified properties are using HandleRepNotifyForGameplayAttribute() within their rep notify function
	for (const FProperty* Property : RepNotifiedProperties)
	{
		if (!Property)
		{
			continue;
		}
		
		const UBlueprint* BlueprintOwner = UBlueprint::GetBlueprintFromClass(Property->GetOwnerClass());
		if (!BlueprintOwner)
		{
			continue;
		}

		GBA_LOG(
			VeryVerbose,
			TEXT("\t Property: %s, PropertyClass: %s, OwnerClass: %s, BlueprintOwner: %s"),
			*GetNameSafe(Property),
			*Property->GetClass()->GetName(),
			*GetNameSafe(Property->GetOwnerClass()),
			*GetNameSafe(BlueprintOwner)
		)

		// Figure out which of the HandleRepNotify method we should use for validation based on FProperty* type
		if (!RepNotifierHandlerNames.Contains(Property->GetCPPType()))
		{
			// Not a property type we care about
			continue;
		}
		
		const FString RepNotifyHandlerFunctionName = RepNotifierHandlerNames.FindChecked(Property->GetCPPType());

		// Get all graphs for the owner Blueprint of this property, to check if it has the corresponding rep notify function
		TArray<UEdGraph*> Graphs;
		BlueprintOwner->GetAllGraphs(Graphs);
		
		// Get the proper ed graph for that notify prop
		const FString RepNotifyFunctionName = FString::Printf(TEXT("OnRep_%s"), *Property->GetName());
		UEdGraph** FoundNotifyGraph = Graphs.FindByPredicate([RepNotifyFunctionName](const UEdGraph* Graph)
		{
			return Graph->GetName() == RepNotifyFunctionName;
		});

		// No found rep notify graph, report as error
		if (FoundNotifyGraph == nullptr)
		{
			Result = EDataValidationResult::Invalid;
			ValidationErrors.Add(FText::Format(
				LOCTEXT("Invalid_RepNotify", "Property {0} Replication option is set to RepNotify but no rep notify function with name \"{1}\" could be found."),
				FText::FromString(Property->GetName()),
				FText::FromString(RepNotifyFunctionName)
			));
			continue;
		}

		if (const UEdGraph* NotifyGraph = *FoundNotifyGraph)
		{
			TArray<UK2Node_CallFunction*> FunctionNodes;
			NotifyGraph->GetNodesOfClass(FunctionNodes);
			
			GBA_LOG(VeryVerbose, TEXT("UGBAAttributeSetBlueprintBase::IsDataValidRepNotifies - FunctionNodes: %d (Graph: %s, Property: %s)"), FunctionNodes.Num(), *NotifyGraph->GetName(), *Property->GetName())

			TArray<UK2Node_CallFunction*> HandleFunctions = FunctionNodes.FilterByPredicate([RepNotifyHandlerFunctionName](const UK2Node_CallFunction* Function)
			{
				return RepNotifyHandlerFunctionName == Function->GetFunctionName().ToString() && IsNodeWiredToEntry(Function);
			});

			// No found "HandleRepNotifyForGameplayAttributeData" (or HandleRepNotifyForGameplayClampedAttributeData) K2 node or not wired to entry node, report as error
			if (HandleFunctions.IsEmpty())
			{
				Result = EDataValidationResult::Invalid;
				ValidationErrors.Add(FText::Format(
					LOCTEXT("Invalid_RepNotify_MissingHandle", "Property {0} is replicated and has a rep notify function but is missing a required call to {1}(). "),
					FText::FromString(Property->GetName()),
					FText::FromString(RepNotifyHandlerFunctionName)
				));

				// GBA_NS_LOG(Warning, TEXT("Must be one of: %s"), *FString::Join(RepNotifierHandlerNames, TEXT(", ")))
				continue;
			}

			// Check AttributeData passed in is correct one based on the containing rep notify
			for (const UK2Node_CallFunction* HandleFunction : HandleFunctions)
			{
				if (!HandleFunction)
				{
					continue;
				}
				
				if (const UEdGraphPin* Pin = HandleFunction->FindPin(TEXT("InAttribute")))
				{
					for (const UEdGraphPin* LinkedTo : Pin->LinkedTo)
					{
						if (!LinkedTo)
						{
							continue;
						}

						const UK2Node_VariableGet* VarNode = Cast<UK2Node_VariableGet>(LinkedTo->GetOwningNode());
						if (!VarNode)
						{
							continue;
						}

						FString MemberName = VarNode->VariableReference.GetMemberName().ToString();
						if (!MemberName.Equals(Property->GetName()))
						{
							Result = EDataValidationResult::Invalid;
							ValidationErrors.Add(FText::Format(
								LOCTEXT("Invalid_RepNotify_HandlePropertyName", "OnRep_{0} is calling {2}() with an incorrect InAttribute (Expected: {0}, Current: {1})"),
								FText::FromString(Property->GetName()),
								FText::FromString(MemberName),
								FText::FromString(RepNotifyHandlerFunctionName)
							));
						}
						
						GBA_LOG(VeryVerbose, TEXT("MemberName: %s, LinkedTo: %s, OwningNode: %s, InputPin: %s"), *MemberName, *LinkedTo->GetName(), *GetNameSafe(VarNode), *Pin->GetName())
					}
				}
			}
		}
	}
	
	return Result;
}

bool UGBAAttributeSetBlueprintBase::IsNodeWiredToEntry(const UK2Node* InNode)
{
	if (!InNode)
	{
		return false;
	}

	if (InNode->IsA(UK2Node_FunctionEntry::StaticClass()))
	{
		return true;
	}

	const UEdGraphPin* InputPin = FindGraphNodePin(InNode, EGPD_Input);
	if (!InputPin)
	{
		return false;
	}

	bool bHasPinWiredToEntry = false;
	for (const UEdGraphPin* LinkedTo : InputPin->LinkedTo)
	{
		if (!LinkedTo)
		{
			continue;
		}

		UEdGraphNode* OwningNode = LinkedTo->GetOwningNode();
		bHasPinWiredToEntry |= IsNodeWiredToEntry(Cast<UK2Node>(OwningNode));
		GBA_LOG(VeryVerbose, TEXT("UGBAAttributeSetBlueprintBase::IsNodeWiredToEntry - LinkedTo: %s, OwningNode: %s, InputPin: %s"), *LinkedTo->GetName(), *GetNameSafe(OwningNode), *InputPin->GetName())
	}

	return bHasPinWiredToEntry;
}

UEdGraphPin* UGBAAttributeSetBlueprintBase::FindGraphNodePin(const UEdGraphNode* InNode, const EEdGraphPinDirection InDirection)
{
	UEdGraphPin* Pin = nullptr;
	for (int32 Idx = 0; Idx < InNode->Pins.Num(); Idx++)
	{
		if (InNode->Pins[Idx]->Direction == InDirection)
		{
			Pin = InNode->Pins[Idx];
			break;
		}
	}

	return Pin;
}
#endif

TMap<FString, TSharedPtr<FAttributeMetaData>> UGBAAttributeSetBlueprintBase::GetAttributesMetaData() const
{
	return AttributesMetaData;
}

void UGBAAttributeSetBlueprintBase::InitClampedAttributeDataProperties()
{
	for (TFieldIterator<FProperty> It(GetClass(), EFieldIteratorFlags::IncludeSuper); It; ++It)
	{
		FProperty* Property = *It;
		if (!IsGameplayAttributeDataClampedProperty(Property))
		{
			continue;
		}
		
		const FStructProperty* StructProperty = CastField<FStructProperty>(Property);
		check(StructProperty);
		FGameplayAttributeData* DataPtr = StructProperty->ContainerPtrToValuePtr<FGameplayAttributeData>(this);
		check(DataPtr);
		
		FGameplayAttribute Attribute = FGameplayAttribute(Property);
		float NewValue = Attribute.GetNumericValue(this);
		NewValue = GetClampedValueForClampedProperty(Attribute, NewValue);
		DataPtr->SetBaseValue(NewValue);
		DataPtr->SetCurrentValue(NewValue);
	}
}

void UGBAAttributeSetBlueprintBase::InitDataTableProperties(const UDataTable* DataTable)
{
	if (!DataTable)
	{
		GBA_NS_LOG(Error, TEXT("Error with datatable initialization. Datatable is invalid."))
		return;
	}

	static const FString Context = FString(TEXT("UGBAAttributeSetBlueprintBase::BindToMetaDataTable"));

	const FString AttributeSetName = FGBAUtils::GetAttributeClassName(GetNameSafe(GetClass()));
	for (TFieldIterator<FProperty> It(GetClass(), EFieldIteratorFlags::IncludeSuper); It; ++It)
	{
		FProperty* Property = *It;
		const FNumericProperty* NumericProperty = CastField<FNumericProperty>(Property);
		
		if (NumericProperty)
		{
			FString RowNameStr = FString::Printf(TEXT("%s.%s"), *AttributeSetName, *Property->GetName());

			if (const FAttributeMetaData* MetaData = DataTable->FindRow<FAttributeMetaData>(FName(*RowNameStr), Context, false))
			{
				void* Data = NumericProperty->ContainerPtrToValuePtr<void>(this);
				NumericProperty->SetFloatingPointPropertyValue(Data, MetaData->BaseValue);
			}
		}
		else if (FGameplayAttribute::IsGameplayAttributeDataProperty(Property))
		{
			FString RowNameStr = FString::Printf(TEXT("%s.%s"), *AttributeSetName, *Property->GetName());
			if (FAttributeMetaData* MetaData = DataTable->FindRow<FAttributeMetaData>(FName(*RowNameStr), Context, false))
			{
				const FStructProperty* StructProperty = CastField<FStructProperty>(Property);
				check(StructProperty);
				FGameplayAttributeData* DataPtr = StructProperty->ContainerPtrToValuePtr<FGameplayAttributeData>(this);
				check(DataPtr);
				
				TSharedRef<FAttributeMetaData> AttributeMetaData = MakeShared<FAttributeMetaData>(*MetaData);
				AttributesMetaData.Add(Property->GetName(), AttributeMetaData);

				// Since this initialization won't run into any of the code path for the attribute set (like PreAttributeChange)
				//
				// We ensure base value is clamped to its higher / lower bounds in the rare case that users set up a base value that is not within their
				// configured min and max values
				float BaseValue = AttributeMetaData->BaseValue;
				if (IsValidAttributeMetadata(AttributeMetaData))
				{
					BaseValue = FMath::Clamp(BaseValue, AttributeMetaData->MinValue, AttributeMetaData->MaxValue);
				}
				
				DataPtr->SetBaseValue(BaseValue);
				DataPtr->SetCurrentValue(BaseValue);
			}
		}
	}
}

bool UGBAAttributeSetBlueprintBase::IsValidClampedProperty(const FGameplayAttribute& Attribute)
{
	if (IsGameplayAttributeDataClampedProperty(Attribute.GetUProperty()))
	{
		const FGBAGameplayClampedAttributeData* Clamped = static_cast<FGBAGameplayClampedAttributeData*>(Attribute.GetGameplayAttributeData(this));
		// Valid whenever we are sure it is a FGBAGameplayClampedAttributeData
		// We'll handle invalidity of lower / max bounds in GetClampedValueForClampedProperty
		return Clamped != nullptr;
	}
	
	return false;
}

float UGBAAttributeSetBlueprintBase::GetClampedValueForClampedProperty(const FGameplayAttribute& Attribute, const float InValue)
{
	float NewValue = InValue;

	if (IsGameplayAttributeDataClampedProperty(Attribute.GetUProperty()))
	{
		if (const FGBAGameplayClampedAttributeData* Clamped = static_cast<FGBAGameplayClampedAttributeData*>(Attribute.GetGameplayAttributeData(this)))
		{
			float MinValue;
			const bool bIsMinValid = Clamped->MinValue.GetValueForClamping(this, MinValue);
			
			float MaxValue;
			const bool bIsMaxValid = Clamped->MaxValue.GetValueForClamping(this, MaxValue);

			// If both min / max are valid, usual clamp
			if (bIsMinValid && bIsMaxValid)
			{
				// GBA_LOG(VeryVerbose, TEXT("UGBAAttributeSetBlueprintBase::GetClampedValueForClampedProperty - Clamp %f between %f and %f"), NewValue, MinValue, MaxValue);
				NewValue = FMath::Clamp(NewValue, MinValue, MaxValue);
			}
			// If only min is valid, then clamp using the lower bound only
			else if (bIsMinValid)
			{
				// GBA_LOG(VeryVerbose, TEXT("UGBAAttributeSetBlueprintBase::GetClampedValueForClampedProperty - Clamp %f using only min %f (max invalid)"), NewValue, MinValue);
				NewValue = FMath::Max(NewValue, MinValue);
			}
			// If only max is valid, then clamp using the higher bound only
			else if (bIsMaxValid)
			{
				// GBA_LOG(VeryVerbose, TEXT("UGBAAttributeSetBlueprintBase::GetClampedValueForClampedProperty - Clamp %f using only max %f (min invalid)"), NewValue, MaxValue);
				NewValue = FMath::Min(NewValue, MaxValue);
			}
			else
			{
				GBA_LOG(
					Warning,
					TEXT("UGBAAttributeSetBlueprintBase::GetClampedValueForClampedProperty - "
					"Clamping for Gameplay Clamped Attribute %s was disabled because Min and Max values are incorrrect"
					"(Min: %s, Max: %s)"),
					*Attribute.GetName(),
					*Clamped->MinValue.ToString(),
					*Clamped->MaxValue.ToString()
				)
			}
		}
	}
	
	return NewValue;
}

bool UGBAAttributeSetBlueprintBase::IsValidAttributeMetadata(const FAttributeMetaData& InAttributeMetadata)
{
	return InAttributeMetadata.MinValue < InAttributeMetadata.MaxValue;
}

bool UGBAAttributeSetBlueprintBase::IsValidAttributeMetadata(const TSharedPtr<FAttributeMetaData>& InAttributeMetadata)
{
	if (!InAttributeMetadata.IsValid())
	{
		return false;
	}
	
	return IsValidAttributeMetadata(*InAttributeMetadata.Get());
}

bool UGBAAttributeSetBlueprintBase::HasClampedMetaData(const FGameplayAttribute& Attribute)
{
	const FString AttributeName = Attribute.GetName();
	if (AttributesMetaData.Contains(AttributeName))
	{
		return IsValidAttributeMetadata(AttributesMetaData.FindChecked(AttributeName));
	}
	
	return false;
}

float UGBAAttributeSetBlueprintBase::GetClampedValueForMetaData(const FGameplayAttribute& Attribute, const float InValue)
{
	float NewValue = InValue;
	const FString AttributeName = Attribute.GetName();
	
	if (AttributesMetaData.Contains(AttributeName))
	{
		const TSharedPtr<FAttributeMetaData> MetaData = AttributesMetaData.FindChecked(AttributeName);
		if (MetaData.IsValid())
		{
			if (IsValidAttributeMetadata(MetaData))
			{
				NewValue = FMath::Clamp(NewValue, MetaData->MinValue, MetaData->MaxValue);
			}
			else
			{
				// This is technically not an error / warning, because DataTables min / max values are usually not handled and have no effect
				// Using verbose lvl here to prevent flooding the output log in the likely cases of rows with Min / Max columns not used (being 0.f)
				GBA_LOG(
					Verbose,
					TEXT("UGBAAttributeSetBlueprintBase::GetClampedValueForMetaData - "
					"Clamping from MetaData table for Attribute %s was disabled because Min and Max values are incorrrect "
					"(Min must be lower than Max - Min: %f, Max: %f)"),
					*AttributeName,
					MetaData->MinValue,
					MetaData->MaxValue
				)
			}
		}
	}
	
	return NewValue;
}

void UGBAAttributeSetBlueprintBase::GetAllBlueprintReplicatedProps(TArray<FProperty*>& OutProperties, const EPropertyFlags InCheckFlag) const
{
	GetAllBlueprintReplicatedProps(GetClass(), OutProperties, InCheckFlag);
}

void UGBAAttributeSetBlueprintBase::GetAllBlueprintReplicatedProps(UClass* InClass, TArray<FProperty*>& OutProperties, const EPropertyFlags InCheckFlag) const
{
	const UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(InClass);
	if (!BPClass)
	{
		return;
	}
	
	uint32 PropertiesLeft = BPClass->NumReplicatedProperties;

	for (TFieldIterator<FProperty> It(BPClass, EFieldIteratorFlags::ExcludeSuper); It && PropertiesLeft > 0; ++It)
	{
		FProperty* Prop = *It;
		if (!Prop || !FGBAUtils::IsValidCPPType(Prop->GetCPPType()))
		{
			continue;
		}
		
		if (Prop != nullptr && Prop->GetPropertyFlags() & InCheckFlag)
		{
			PropertiesLeft--;
			OutProperties.Add(Prop);
		}
	}

	UBlueprintGeneratedClass* SuperBPClass = Cast<UBlueprintGeneratedClass>(BPClass->GetSuperStruct());
	if (SuperBPClass != nullptr)
	{
		GetAllBlueprintReplicatedProps(SuperBPClass, OutProperties);
	}
}

bool UGBAAttributeSetBlueprintBase::GetAttributeDataPropertyName(const FGameplayAttributeData& InAttributeData, FString& OutPropertyName)
{
	const UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(GetClass());
	if (!BPClass)
	{
		return false;
	}

	// Note: One possible improvement to this would be to cache the result in an internal map TMap<FGameplayAttribute, FString>
	// and avoid further iterations over BP properties if we already know its name.
	//
	// But the problem lies with the original input parameter that is passed down from Blueprint, the FGameplayAttributeData
	// property. We can get the FGameplayAttribute (where we can read its name) from an FProperty or get the corresponding
	// FGameplayAttributeData from a FGameplayAttribute, but we can't get a FGameplayAttribute out of a
	// FGameplayAttributeData.
	//
	// Even with a cache, we wouldn't be able to query the map from a FGameplayAttributeData as the struct doesn't implement
	// GetTypeHash() and equality operators (whereas FGameplayAttribute do).

	uint32 PropertiesLeft = BPClass->NumReplicatedProperties;
	for (TFieldIterator<FProperty> It(BPClass, EFieldIteratorFlags::ExcludeSuper); It && PropertiesLeft > 0; ++It)
	{
		const FProperty* Prop = *It;
		if (Prop != nullptr && Prop->GetPropertyFlags() & CPF_Net)
		{
			PropertiesLeft--;

			// Ignore any props that are not valid GameplayAttributeData or one of its child struct
			if (!FGameplayAttribute::IsGameplayAttributeDataProperty(Prop))
			{
				continue;
			}

			if (const FGameplayAttributeData* DataPtr = Prop->ContainerPtrToValuePtr<FGameplayAttributeData>(this))
			{
				if (DataPtr == &InAttributeData)
				{
					FString AuthoredName = Prop->GetAuthoredName();
					GBA_LOG(Verbose, TEXT("\t\t Found matching property for AuthoredName: %s"), *AuthoredName)
					OutPropertyName = MoveTemp(AuthoredName);
					return true;
				}
			}
		}
	}
	
	return false;
}

#undef LOCTEXT_NAMESPACE
