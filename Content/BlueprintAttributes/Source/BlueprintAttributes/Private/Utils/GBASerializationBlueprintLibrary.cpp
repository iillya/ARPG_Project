// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "Utils/GBASerializationBlueprintLibrary.h"

#include "AbilitySystemComponent.h"
#include "GBALog.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/MemoryWriter.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Utils/GBAUtils.h"

const TArray<uint8>& UGBASerializationBlueprintLibrary::SerializeAbilitySystemComponent(UAbilitySystemComponent* InASC, TArray<uint8>& InData, const bool bIsSaving, const bool bIsASCImplementingSerialize)
{
	GBA_NS_LOG(Display, TEXT("InASC: %s, InData: %d, bIsSaving: %s"), *GetNameSafe(InASC), InData.Num(), *LexToString(bIsSaving))

	// Archive, MemoryWrite on Saving, MemoryReader on Loading
	TUniquePtr<FArchive> MemoryArchive;
	if (bIsSaving)
	{
		MemoryArchive = MakeUnique<FMemoryWriter>(InData);
	}
	else
	{
		MemoryArchive = MakeUnique<FMemoryReader>(InData);
	}

	constexpr bool bInLoadIfFindFails = true;
	TUniquePtr<FObjectAndNameAsStringProxyArchive> Archive = MakeUnique<FObjectAndNameAsStringProxyArchive>(*MemoryArchive, bInLoadIfFindFails);
	Archive->ArIsSaveGame = true;

	// Serialize the ASC
	
	if (bIsASCImplementingSerialize)
	{
		// This implies the passed in Ability System Component is implementing Serialize for SaveGame and
		// is calling Serialize on each of its AttributeSets.
		InASC->Serialize(*Archive);
	}
	else
	{
		// ASC not implementing Serialize(), gather all spawned attribute sets and serialize individual attributes
		FGBAUtils::SerializeAbilitySystemComponentAttributes(InASC, *Archive);
		
	}

	MemoryArchive->Close();

	// Release proxies first
	Archive.Reset();

	// Then our memory writer
	MemoryArchive.Reset();

	return MoveTemp(InData);
}
