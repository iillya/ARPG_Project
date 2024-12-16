// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "Utils/GBAUtils.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemTestAttributeSet.h"
#include "AttributeSet.h"
#include "Abilities/GBAAttributeSetBlueprintBase.h"
#include "UObject/UObjectIterator.h"

FString FGBAUtils::GetAttributeClassName(const UClass* Class)
{
	if (!Class)
	{
		return TEXT("None");
	}

#if WITH_EDITORONLY_DATA
	// ClassGeneratedBy - This is wrong in cooked builds
	if (!Class->ClassGeneratedBy)
	{
		return Class->GetName();
	}
#endif

	return GetAttributeClassName(Class->GetName());
}

FString FGBAUtils::GetAttributeClassName(FString ClassName)
{
	if (ClassName.IsEmpty())
	{
		return ClassName;
	}

	ClassName.RemoveFromEnd(TEXT("_C"));
	return ClassName;
}

void FGBAUtils::GetAllAttributeProperties(TArray<FProperty*>& OutProperties, const FString InFilterMetaStr, const bool bInUseEditorOnlyData)
{
	// Gather all UAttribute classes
	for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
	{
		const UClass* Class = *ClassIt;
		if (IsValidAttributeClass(Class))
		{
			if (bInUseEditorOnlyData)
			{
#if WITH_EDITOR
				// Allow entire classes to be filtered globally
				if (Class->HasMetaData(TEXT("HideInDetailsView")))
				{
					continue;
				}
#endif
			}

			if (Class == UAbilitySystemTestAttributeSet::StaticClass())
			{
				continue;
			}

			GetAllAttributeFromClass(Class, OutProperties, InFilterMetaStr, bInUseEditorOnlyData);
		}

#if WITH_EDITOR
		if (bInUseEditorOnlyData)
		{
			// UAbilitySystemComponent can add 'system' attributes
			if (Class->IsChildOf(UAbilitySystemComponent::StaticClass()) && !Class->ClassGeneratedBy)
			{
				for (TFieldIterator<FProperty> PropertyIt(Class, EFieldIteratorFlags::ExcludeSuper); PropertyIt; ++PropertyIt)
				{
					FProperty* Property = *PropertyIt;


					// SystemAttributes have to be explicitly tagged
					if (Property->HasMetaData(TEXT("SystemGameplayAttribute")) == false)
					{
						continue;
					}
					OutProperties.Add(Property);
				}
			}
		}
#endif
	}
}

void FGBAUtils::GetAllAttributeFromClass(const UClass* InClass, TArray<FProperty*>& OutProperties, const FString InFilterMetaStr, const bool bInUseEditorOnlyData)
{
	check(InClass);
	
	for (TFieldIterator<FProperty> PropertyIt(InClass, EFieldIteratorFlags::ExcludeSuper); PropertyIt; ++PropertyIt)
	{
		FProperty* Property = *PropertyIt;

		if (bInUseEditorOnlyData)
		{
#if WITH_EDITOR
			if (!InFilterMetaStr.IsEmpty() && Property->HasMetaData(*InFilterMetaStr))
			{
				continue;
			}

			// Allow properties to be filtered globally (never show up)
			if (Property->HasMetaData(TEXT("HideInDetailsView")))
			{
				continue;
			}
#endif

			// Only allow field of expected types
			FString CPPType = Property->GetCPPType();
			if (!IsValidCPPType(CPPType))
			{
				continue;
			}
		}

		OutProperties.Add(Property);
	}
}

bool FGBAUtils::IsValidAttributeClass(const UClass* Class)
{
	if (!Class)
	{
		return false;
	}

	if (!Class->IsChildOf(UAttributeSet::StaticClass()))
	{
		return false;
	}

#if WITH_EDITORONLY_DATA
	// ClassGeneratedBy - This is wrong in cooked builds
	if (Class->ClassGeneratedBy)
	{
		// Only allow BP subclass we know
		if (!Class->IsChildOf(UGBAAttributeSetBlueprintBase::StaticClass()))
		{
			return false;
		}

		// TODO: Check if this can be checked with Object Flags instead of comparing class name
		const FString Name = Class->GetName();
		if (Name.StartsWith(TEXT("SKEL_")) || Name.StartsWith(TEXT("REINST_")))
		{
			return false;
		}
	}
#endif

	return true;
}


template <class TReturnType>
TReturnType* GetIfValid(TWeakObjectPtr<TReturnType> WeakObjectPtr)
{
	return WeakObjectPtr.IsValid() ? WeakObjectPtr.Get() : nullptr;
}

bool FGBAUtils::IsValidCPPType(const FString& InCPPType)
{
	if (InCPPType == TEXT("FGameplayAttributeData"))
	{
		return true;
	}

	if (InCPPType == TEXT("FGBAGameplayClampedAttributeData"))
	{
		return true;
	}

	// TODO: Check using FGameplayAttribute::IsGameplayAttributeDataProperty

	return false;
}

void FGBAUtils::SerializeAttributeSet(UAttributeSet* InAttributeSet, FArchive& InArchive)
{
	if (!InArchive.IsSaveGame())
	{
		return;
	}

	check(InAttributeSet);

	const UAbilitySystemComponent* ASC = InAttributeSet->GetOwningAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	for (TFieldIterator<FProperty> PropertyIt(InAttributeSet->GetClass(), EFieldIteratorFlags::ExcludeSuper); PropertyIt; ++PropertyIt)
	{
		FProperty* Property = *PropertyIt;
		if (!Property)
		{
			continue;
		}

		FString PropertyName = Property->GetName();
		FGameplayAttribute Attribute = FGameplayAttribute(Property);
		if (!Attribute.IsValid())
		{
			continue;
		}

		// Filter out any properties not marked with SaveGame
		if (!(Property->GetPropertyFlags() & CPF_SaveGame))
		{
			continue;
		}

		float BaseValue = 0.f;
		float CurrentValue = 0.f;
		if (InArchive.IsSaving())
		{
			// On saving, read from archive
			BaseValue = ASC->GetNumericAttributeBase(Attribute);
			CurrentValue = ASC->GetNumericAttribute(Attribute);
		}

		// Serialize, in and out
		InArchive << BaseValue;
		InArchive << CurrentValue;

		if (InArchive.IsLoading())
		{
			const FStructProperty* StructProperty = CastField<FStructProperty>(Property);
			check(StructProperty);

			FGameplayAttributeData* DataPtr = StructProperty->ContainerPtrToValuePtr<FGameplayAttributeData>(InAttributeSet);
			check(DataPtr);

			DataPtr->SetBaseValue(BaseValue);
			DataPtr->SetCurrentValue(CurrentValue);

			// Or simpler - but only for base value
			// SetNumericAttributeBase(Attribute, BaseValue);
		}
	}
}

void FGBAUtils::SerializeAbilitySystemComponentAttributes(const UAbilitySystemComponent* InASC, FArchive& InArchive)
{
	if (!InArchive.IsSaveGame())
	{
		return;
	}

	check(InASC);

	const TArray<UAttributeSet*>& AttributeSets = InASC->GetSpawnedAttributes();
	for (UAttributeSet* AttributeSet : AttributeSets)
	{
		if (AttributeSet)
		{
			// Assuming AttributeSet is implementing serialize and invokes FGBAUtils::SerializeAttributeSet:
			AttributeSet->Serialize(InArchive);

			// Could be also:
			// SerializeAttributeSet(AttributeSet, InArchive);
		}
	}
}
