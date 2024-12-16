// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Blueprint.h"
#include "GBAAttributeSetBlueprint.generated.h"

/**
 * A Gameplay Blueprint Attribute Set is essentially a specialized Blueprint whose graphs control a GAS Attribute Set.
 * 
 * The factory should pick this for you automatically.
 * 
 * Defines the set of GameplayAttributes for your game.
 * 
 * Games should subclass this (in Blueprints) and add FGameplayAttributeData properties to represent attributes like health, damage, etc
 * 
 * AttributeSets are then registered with the AbilitySystemComponent. It is often desired to have several sets per project that could inherit
 * from each other. You could make a base health set, then have a player set that inherits from it and adds more attributes.
 */
UCLASS(BlueprintType)
class BLUEPRINTATTRIBUTES_API UGBAAttributeSetBlueprint : public UBlueprint
{
	GENERATED_BODY()

public:
	virtual ~UGBAAttributeSetBlueprint() override;

#if WITH_EDITOR
	//~ Begin UBlueprint interface
	virtual bool SupportedByDefaultBlueprintFactory() const override
	{
		return false;
	}
	//~ End of UBlueprint interface
#endif
	
	//~ Begin UObject interface
	virtual void PostLoad() override;
	//~ End of UObject interface
	
#if WITH_EDITOR
	void RegisterDelegates();
	void OnPreVariableChange(UObject* InObject);
	void HandleVariableChanges(const UBlueprint* InBlueprint);
	void OnPostVariableChange(UBlueprint* InBlueprint) const;
	void OnPostCompiled(UBlueprint* InBlueprint);
	static void OnVariableAdded(const FName& Name);
	static void OnVariableRemoved(const FName& Name);
	void OnVariableRenamed(const FName& InOldVarName, const FName& InNewVarName) const;
	void OnVariableTypeChanged(const FName& InVarName, const FEdGraphPinType& InOldPinType, const FEdGraphPinType& InNewPinType) const;
#endif

private:
	
#if WITH_EDITORONLY_DATA
	TArray<FBPVariableDescription> LastNewVariables;
	
	TArray<FBPVariableDescription> AddedVariables;
	TArray<FBPVariableDescription> RenamedVariables;
	TArray<FBPVariableDescription> ChangedTypeVariables;
#endif
};
