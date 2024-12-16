// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "Blueprint/GBAAttributeSetBlueprint.h"

#include "GBADelegates.h"
#include "GBALog.h"
#include "Misc/EngineVersionComparison.h"
#include "UObject/UObjectGlobals.h"

#if WITH_EDITOR
#if UE_VERSION_NEWER_THAN(5, 1, -1)
#include "RigVMDeveloperTypeUtils.h"
#else
#include "RigVMTypeUtils.h"
#endif
#endif

UGBAAttributeSetBlueprint::~UGBAAttributeSetBlueprint()
{
	GBA_LOG(VeryVerbose, TEXT("UGBAAttributeSetBlueprint::~UGBAAttributeSetBlueprint - Destructor"))
#if WITH_EDITOR
	FCoreUObjectDelegates::OnObjectModified.RemoveAll(this);
	OnChanged().RemoveAll(this);
	OnCompiled().RemoveAll(this);
#endif
}

void UGBAAttributeSetBlueprint::PostLoad()
{
	Super::PostLoad();
#if WITH_EDITOR
	RegisterDelegates();
#endif
}

#if WITH_EDITOR

void UGBAAttributeSetBlueprint::RegisterDelegates()
{
	if (IsTemplate())
	{
		return;
	}
	
	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprint::RegisterDelegates - Setup delegates for %s"), *GetName())

	FCoreUObjectDelegates::OnObjectModified.RemoveAll(this);
	OnChanged().RemoveAll(this);
	OnCompiled().RemoveAll(this);

	FCoreUObjectDelegates::OnObjectModified.AddUObject(this, &UGBAAttributeSetBlueprint::OnPreVariableChange);
	OnChanged().AddUObject(this, &UGBAAttributeSetBlueprint::OnPostVariableChange);
	OnCompiled().AddUObject(this, &UGBAAttributeSetBlueprint::OnPostCompiled);
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void UGBAAttributeSetBlueprint::OnPreVariableChange(UObject* InObject)
{
	if (InObject != this)
	{
		return;
	}

	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprint::OnPreVariableChange %s"), *GetNameSafe(InObject))

	LastNewVariables = NewVariables;
}

void UGBAAttributeSetBlueprint::HandleVariableChanges(const UBlueprint* InBlueprint)
{
	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprint::OnPostVariableChange %s"), *GetNameSafe(InBlueprint))

	TMap<FGuid, int32> NewVariablesByGuid;
	for (int32 VarIndex = 0; VarIndex < NewVariables.Num(); VarIndex++)
	{
		NewVariablesByGuid.Add(NewVariables[VarIndex].VarGuid, VarIndex);
	}

	TMap<FGuid, int32> OldVariablesByGuid;
	for (int32 VarIndex = 0; VarIndex < LastNewVariables.Num(); VarIndex++)
	{
		OldVariablesByGuid.Add(LastNewVariables[VarIndex].VarGuid, VarIndex);
	}

	for (const FBPVariableDescription& OldVariable : LastNewVariables)
	{
		if (!NewVariablesByGuid.Contains(OldVariable.VarGuid))
		{
			OnVariableRemoved(OldVariable.VarName);
		}
	}

	for (const FBPVariableDescription& NewVariable : NewVariables)
	{
		if (!OldVariablesByGuid.Contains(NewVariable.VarGuid))
		{
			OnVariableAdded(NewVariable.VarName);
			continue;
		}

		const int32 OldVarIndex = OldVariablesByGuid.FindChecked(NewVariable.VarGuid);
		const FBPVariableDescription& OldVariable = LastNewVariables[OldVarIndex];
		if (OldVariable.VarName != NewVariable.VarName)
		{
			OnVariableRenamed(OldVariable.VarName, NewVariable.VarName);
		}

		if (OldVariable.VarType != NewVariable.VarType)
		{
			OnVariableTypeChanged(NewVariable.VarName, OldVariable.VarType, NewVariable.VarType);
		}
	}

	LastNewVariables = NewVariables;
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void UGBAAttributeSetBlueprint::OnPostVariableChange(UBlueprint* InBlueprint) const
{
	if (InBlueprint != this)
	{
		return;
	}

	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprint::OnPostVariableChange - %s"), *GetNameSafe(InBlueprint))
	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprint::OnPostVariableChange - IsPossiblyDirty: %s"), IsPossiblyDirty() ? TEXT("true") : TEXT("false"))
	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprint::OnPostVariableChange - IsUpToDate: %s"), IsUpToDate() ? TEXT("true") : TEXT("false"))
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void UGBAAttributeSetBlueprint::OnPostCompiled(UBlueprint* InBlueprint)
{
	if (InBlueprint != this)
	{
		return;
	}


	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprint::OnPostCompiled - %s"), *GetNameSafe(InBlueprint))
	HandleVariableChanges(InBlueprint);

	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprint::OnPostCompiled - IsPossiblyDirty: %s"), IsPossiblyDirty() ? TEXT("true") : TEXT("false"))
	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprint::OnPostCompiled - IsUpToDate: %s"), IsUpToDate() ? TEXT("true") : TEXT("false"))

	if (const UPackage* Package = GetPackage())
	{
		FGBADelegates::OnPostCompile.Broadcast(Package->GetFName());
	}
}

void UGBAAttributeSetBlueprint::OnVariableAdded(const FName& Name)
{
	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprint::OnVariableAdded Name: %s"), *Name.ToString())
	FGBADelegates::OnVariableAdded.Broadcast(Name);
}

void UGBAAttributeSetBlueprint::OnVariableRemoved(const FName& Name)
{
	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprint::OnVariableRemoved Name: %s"), *Name.ToString())
	FGBADelegates::OnVariableRemoved.Broadcast(Name);
}

void UGBAAttributeSetBlueprint::OnVariableRenamed(const FName& InOldVarName, const FName& InNewVarName) const
{
	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprint::OnVariableRenamed InOldVarName: %s, InNewVarName: %s"), *InOldVarName.ToString(), *InNewVarName.ToString())

	const UPackage* Package = GetPackage();
	if (!Package)
	{
		GBA_LOG(Warning, TEXT("UGBAAttributeSetBlueprint::OnVariableRenamed SelfPackage nullptr"))
		return;
	}

	// Broadcast renamed event, the subsystem will handle the rest
	FGBADelegates::OnVariableRenamed.Broadcast(Package->GetFName(), InOldVarName, InNewVarName);
}

void UGBAAttributeSetBlueprint::OnVariableTypeChanged(const FName& InVarName, const FEdGraphPinType& InOldPinType, const FEdGraphPinType& InNewPinType) const
{
	const FString OldVarTypeStr = FString::Printf(TEXT("Category: %s, SubCategory: %s"), *InOldPinType.PinCategory.ToString(), *InOldPinType.PinSubCategory.ToString());
	const FString NewVarTypeStr = FString::Printf(TEXT("Category: %s, SubCategory: %s"), *InNewPinType.PinCategory.ToString(), *InNewPinType.PinSubCategory.ToString());

	FString CPPType;
	UObject* CPPTypeObject = nullptr;
	RigVMTypeUtils::CPPTypeFromPinType(InNewPinType, CPPType, &CPPTypeObject);

	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprint::OnVariableTypeChanged InVarName: %s || InOldPinType: %s || InNewPinType: %s"), *InVarName.ToString(), *OldVarTypeStr, *NewVarTypeStr)
	GBA_LOG(Verbose, TEXT("UGBAAttributeSetBlueprint::OnVariableTypeChanged ==> CPPType: %s || CPPTypeObject: %s"), *CPPType, *GetNameSafe(CPPTypeObject))

	FGBADelegates::OnVariableTypeChanged.Broadcast(InVarName, CPPType, CPPTypeObject);
}

#endif