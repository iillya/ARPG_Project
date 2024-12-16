// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GBAExecutionCalculationBlueprintLibrary.generated.h"

struct FGameplayAttribute;
struct FGameplayEffectAttributeCaptureDefinition;
struct FGameplayEffectContextHandle;
struct FGameplayEffectCustomExecutionOutput;
struct FGameplayEffectCustomExecutionParameters;
struct FGameplayEffectSpec;
struct FGameplayTagContainer;

/**
 * Blueprint library for blueprint attribute sets.
 *
 * Includes Gameplay Effect Execution Calculation helpers for Blueprint implementation of Exec Calc classes.
 */
UCLASS()
class BLUEPRINTATTRIBUTES_API UGBAExecutionCalculationBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Blueprint Attributes | Exec Calc")
	static const FGameplayEffectSpec& GetOwningSpec(const FGameplayEffectCustomExecutionParameters& InExecutionParams);

	UFUNCTION(BlueprintPure, Category = "Blueprint Attributes | Exec Calc")
	static FGameplayEffectContextHandle GetEffectContext(const FGameplayEffectCustomExecutionParameters& InExecutionParams);
	
	UFUNCTION(BlueprintPure, Category = "Blueprint Attributes | Exec Calc")
	static const FGameplayTagContainer& GetSourceTags(const FGameplayEffectCustomExecutionParameters& InExecutionParams);
	
	UFUNCTION(BlueprintPure, Category = "Blueprint Attributes | Exec Calc")
	static const FGameplayTagContainer& GetTargetTags(const FGameplayEffectCustomExecutionParameters& InExecutionParams);
	
	UFUNCTION(BlueprintPure, Category = "Blueprint Attributes | Exec Calc")
	static bool AttemptCalculateCapturedAttributeMagnitude(UPARAM(ref) const FGameplayEffectCustomExecutionParameters& InExecutionParams, UPARAM(ref) const TArray<FGameplayEffectAttributeCaptureDefinition>& InRelevantAttributesToCapture, const FGameplayAttribute InAttribute, float& OutMagnitude);
	
	UFUNCTION(BlueprintCallable, Category = "Blueprint Attributes | Exec Calc")
	static bool AttemptCalculateCapturedAttributeMagnitudeWithBase(UPARAM(ref) const FGameplayEffectCustomExecutionParameters& InExecutionParams, UPARAM(ref) const TArray<FGameplayEffectAttributeCaptureDefinition>& InRelevantAttributesToCapture, const FGameplayAttribute InAttribute, const float InBaseValue, float& OutMagnitude);
	
	UFUNCTION(BlueprintCallable, Category = "Blueprint Attributes | Exec Calc")
	static const FGameplayEffectCustomExecutionOutput& AddOutputModifier(UPARAM(ref) FGameplayEffectCustomExecutionOutput& InExecutionOutput, const FGameplayAttribute InAttribute, const EGameplayModOp::Type InModOp, const float InMagnitude);
};
