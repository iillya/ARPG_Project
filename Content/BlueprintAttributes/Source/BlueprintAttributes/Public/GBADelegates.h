// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UGameplayAbility;

struct BLUEPRINTATTRIBUTES_API FGBADelegates
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FGBAOnVariableAddedOrRemoved, const FName&);
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FGBAOnVariableRenamed, const FName&, const FName&, const FName&);
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FGBAOnVariableTypeChanged, const FName&, FString, UObject*);
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FGBAOnPostCompile, const FName&);
	DECLARE_MULTICAST_DELEGATE_OneParam(FGBAOnPreCompile, const FName&);

	DECLARE_MULTICAST_DELEGATE(FGBAOnRequestDetailsRefresh)

	static FGBAOnVariableAddedOrRemoved OnVariableAdded;
	static FGBAOnVariableAddedOrRemoved OnVariableRemoved;
	static FGBAOnVariableRenamed OnVariableRenamed;
	static FGBAOnVariableTypeChanged OnVariableTypeChanged;
	
	static FGBAOnPreCompile OnPreCompile;
	static FGBAOnPostCompile OnPostCompile;
	
	static FGBAOnRequestDetailsRefresh OnRequestDetailsRefresh;
};
