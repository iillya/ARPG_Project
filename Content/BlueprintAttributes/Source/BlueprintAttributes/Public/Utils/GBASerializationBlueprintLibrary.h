// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GBASerializationBlueprintLibrary.generated.h"

class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FGBAActorSaveData
{
	GENERATED_BODY()

public:

	/* Identifier for which Actor this belongs to */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	FName ActorName;

	/* For movable Actors, keep location,rotation,scale. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	FTransform Transform;

	/* Contains all 'SaveGame' marked variables of the Actor */
	UPROPERTY(BlueprintReadOnly, Category = "Save")
	TArray<uint8> ByteData;
};

UCLASS()
class UGBASaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	FString SaveGameName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	FGBAActorSaveData SavedActor;
};

/**
 * Blueprint library for blueprint attribute sets.
 *
 * Includes serialization helpers, Save Game related.
 */
UCLASS()
class BLUEPRINTATTRIBUTES_API UGBASerializationBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Helper method to serialize an actor's Ability System Component and all of its SaveGame marked FGameplayAttributes.
	 * 
	 * If saving, will write FGameplayAttribute values
	 * 
	 * ```cpp
	 * void UMyAttributeSet::Serialize(FArchive& Ar)
	 * {
	 * 	Super::Serialize(Ar);
	 *
	 * 	if (Ar.IsSaveGame())
	 * 	{
	 * 		FGBAUtils::SerializeAttributeSet(this, Ar);
	 * 	}
	 * }
	 * ```
	 *
	 * TODO: It should ideally use a structured archive and store values along the field path (as a map or an array with
	 * attribute set owner / attribute name)
	 * 
	 * @param InASC Ability System Component from which to serialize the AttributeSets
	 * @param InData The binary data to serialize from and to as an array of bytes
	 * @param bIsSaving Determines if the serialization should read or write from the underlying archive
	 * (This should be true when saving, and false when loading)
	 * @param bIsASCImplementingSerialize Whether the ASC component that is passed in is implementing Serialize(),
	 * and whether we should use it.
	 *					
	 * @returns The input Binary Data modified along the way in case of saving
	 */
	UFUNCTION(BlueprintCallable, Category="Blueprint Attributes | Serialize")
	static const TArray<uint8>& SerializeAbilitySystemComponent(
		UPARAM(ref, DisplayName = "AbilitySystemComponent") UAbilitySystemComponent* InASC,
		UPARAM(ref, DisplayName = "Data") TArray<uint8>& InData,
		const bool bIsSaving = true,
		const bool bIsASCImplementingSerialize = false
	);
};
