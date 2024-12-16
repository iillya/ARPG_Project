// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "AssetTypes/GBABlueprintFactory.h"

#include "BlueprintEditorSettings.h"
#include "GBAEditorLog.h"
#include "Abilities/GBAAttributeSetBlueprintBase.h"
#include "Blueprint/GBAAttributeSetBlueprint.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Misc/MessageDialog.h"

#define LOCTEXT_NAMESPACE "GBABlueprintFactory"

UGBABlueprintFactory::UGBABlueprintFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UGBAAttributeSetBlueprint::StaticClass();
	ParentClass = UGBAAttributeSetBlueprintBase::StaticClass();
}

bool UGBABlueprintFactory::ConfigureProperties()
{
	return true;
}

UObject* UGBABlueprintFactory::FactoryCreateNew(UClass* Class, UObject* InParent, const FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, const FName CallingContext)
{
	// Make sure we are trying to factory a Control Rig Blueprint, then create and init one
	check(Class->IsChildOf(UGBAAttributeSetBlueprint::StaticClass()));

	// From standard factory create new, we omit FKismetEditorUtilities::CanCreateBlueprintOfClass to accomodate
	// UGBAAttributeSetBlueprintBase being NotBlueprintable (we don't want to have this class picked from standard create BP)
	//
	// Class->GetBoolMetaDataHierarchical(FBlueprintMetadata::MD_IsBlueprintBase) would fail and return false, preventing creation
	if (ParentClass == nullptr || !ParentClass->IsChildOf(UGBAAttributeSetBlueprintBase::StaticClass()))
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("ClassName"), ParentClass != nullptr ? FText::FromString(ParentClass->GetName()) : LOCTEXT("Null", "(null)"));
		FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("CannotCreateControlRigBlueprint", "Cannot create an Attribute Set Blueprint based on the class '{ClassName}'."), Args));
		return nullptr;
	}
	
	GBA_EDITOR_LOG(Verbose, TEXT("UGBABlueprintFactory::FactoryCreateNew Create BP"))
	UGBAAttributeSetBlueprint* Blueprint = CastChecked<UGBAAttributeSetBlueprint>(FKismetEditorUtilities::CreateBlueprint(
		ParentClass,
		InParent,
		Name,
		BPTYPE_Normal,
		UGBAAttributeSetBlueprint::StaticClass(),
		UBlueprintGeneratedClass::StaticClass(),
		CallingContext
	));

	if (Blueprint)
	{
		const UBlueprintEditorSettings* Settings = GetMutableDefault<UBlueprintEditorSettings>();
		if (Settings && Settings->bSpawnDefaultBlueprintNodes)
		{
			int32 NodePositionY = 0;
			UEdGraph* EventGraph = Blueprint->UbergraphPages[0];

			// Those are the 3 non-const, no return values events. They appear in event graph
			FKismetEditorUtilities::AddDefaultEventNode(Blueprint, EventGraph, FName(TEXT("K2_PostGameplayEffectExecute")), UGBAAttributeSetBlueprintBase::StaticClass(), NodePositionY);
			FKismetEditorUtilities::AddDefaultEventNode(Blueprint, EventGraph, FName(TEXT("K2_PostAttributeChange")), UGBAAttributeSetBlueprintBase::StaticClass(), NodePositionY);

			// Those are implemented as overridable functions, cause they're either const or return values
			// And AddDefaultEventNode won't work for them (well the nodes are created but will complain on the first compilation if wired
			// FKismetEditorUtilities::AddDefaultEventNode(Blueprint, EventGraph, FName(TEXT("K2_PreAttributeChange")), UGBAAttributeSetBlueprintBase::StaticClass(), NodePositionY);
			// FKismetEditorUtilities::AddDefaultEventNode(Blueprint, EventGraph, FName(TEXT("K2_PreAttributeBaseChange")), UGBAAttributeSetBlueprintBase::StaticClass(), NodePositionY);
			// FKismetEditorUtilities::AddDefaultEventNode(Blueprint, EventGraph, FName(TEXT("K2_PreAttributeChange")), UGBAAttributeSetBlueprintBase::StaticClass(), NodePositionY);
			// FKismetEditorUtilities::AddDefaultEventNode(Blueprint, EventGraph, FName(TEXT("K2_PostAttributeBaseChange")), UGBAAttributeSetBlueprintBase::StaticClass(), NodePositionY);
		}
	}
	
	
	return Blueprint;
}

UObject* UGBABlueprintFactory::FactoryCreateNew(UClass* Class, UObject* InParent, const FName Name, const EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn, NAME_None);
}

#undef LOCTEXT_NAMESPACE
