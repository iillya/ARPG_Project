// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "GBAEditorSubsystem.generated.h"

class FTokenizedMessage;
class IGBAAttributeReferencerHandler;
class IMessageToken;
class IToolkit;
class UEdGraphPin;
class UGameplayEffect;
class UK2Node;
struct FAssetDependency;

/**
 * Editor subsystem to handle Gameplay Attribute property renames in Blueprint.
 *
 * Changing a variable name needs to be handled to prevent crash from happening if any Gameplay Effects is using it, and if
 * that Gameplay Effect was previously opened and focused again in editor (not relevant anymore since rework into using TWeakFieldPtr<FProperty>).
 *
 * The Details customization for the Attribute or Effect using those needs to be updated "live", whereas in the usual case
 * of having Attributes defined in cpp, code needs to be recompiled and editor restarted.
 *
 * With Blueprints, we need a way to rename attributes and have Gameplay Effects (or other K2 nodes using Gameplay Attribute) updated
 * to reference the new property.
 *
 * ---
 *
 * Subsystem register to an OnVariableRename delegate fired off from `UGBAAttributeSetBlueprint`, and handle any editor specific code.
 *
 * When a rename happens, this event fires off and triggers the following logic in this subsystem:
 *
 * 1. Get all referencers to the original Attribute Set Blueprints (its package name)
 * 2. Check if any referencers is currently opened in Editor, store them
 * (TODO: Check if renamed attribute is actually used, a referencer can be referencing other attributes from same BP, in which case closing asset editor is not required)
 * 3. Close any opened referencers in Editor
 * 4. Update CDO for any referencers to update property from Old Attribute property to the new one
 * 5. Reopen any closed editor previously, if any
 */
UCLASS()
class BLUEPRINTATTRIBUTESEDITOR_API UGBAEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	/** The message log category */
	static constexpr const TCHAR* LogName = TEXT("BlueprintAttributesLog");

	/** List of referencer handler registered via RegisterReferencerHandler() */
	TMap<FName, TSharedPtr<IGBAAttributeReferencerHandler>> RegisteredHandlers;

	/** Keeps track of whether we are currently handling a rename (and prevent rename code path to run again when we manually compile the BP at the end of this run) */
	bool bIsHandlingRename = false;
	
	/** List of pending tokenized messages representing an attribute ref updated */
	TArray<TSharedRef<FTokenizedMessage>> PendingMessages;

	/** Data holder for Blueprints / K2 Nodes pin that needs an update */
	struct FPinToModify
	{
		UEdGraphPin* Pin;
		TWeakObjectPtr<UK2Node> BlueprintNode;
		FString OldPropertyName;

		FPinToModify() = default;

		FPinToModify(UEdGraphPin* InPin, const TWeakObjectPtr<UK2Node>& InBlueprintNode, const FString& InOldPropertyName)
			: Pin(InPin)
			, BlueprintNode(InBlueprintNode)
			, OldPropertyName(InOldPropertyName)
		{
		}

		bool operator==(const FPinToModify& InOther) const
		{
			return Pin == InOther.Pin && BlueprintNode == InOther.BlueprintNode;
		}
	};

	//~ Begin UEditorSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//~ End UEditorSubsystem interface
	
	/** Static convenience method to return storm sync notification subsystem */
	static UGBAEditorSubsystem& Get();

	/** Adds a custom referencer handler for given InClassName (without the class prefix, eg. GameplayEffect instead of UGameplayEffect) */
	virtual void RegisterReferencerHandler(const FName& InClassName, const TSharedPtr<IGBAAttributeReferencerHandler>& InHandler);
	
	/** Removes a previously registered handler */
	virtual void UnregisterReferencerHandler(const FName& InClassName);

	/** Returns the associated referencer handler (if any) registered for the class default object of InReferencer.AssetId */
	TSharedPtr<IGBAAttributeReferencerHandler> FindAssetDependencyHandler(const FName& InReferencer, TWeakObjectPtr<UObject>& OutDefaultObject);

	/**
	 * Handler for OnVariableRenamed delegate.
	 *
	 * @param InPackageName The Package Name (eg. /Game/Path/BP_AttributeSet) of the original Attribute Set that owns the renamed Attribute
	 * @param InOldPropertyName The name of the attribute before rename
	 * @param InNewPropertyName The new name of the attribute
	 */
	void HandleAttributeRename(const FName& InPackageName, const FName& InOldPropertyName, const FName& InNewPropertyName);

	/**
	 * Triggered by FGBABlueprintEditor just before FBlueprintEditor::Compile()
	 *
	 * Used to gather the list of references and build a "cache" of Attribute referencer, so that when a rename happens, we can compare the old and new value
	 * to see if an update is needed for the referencer CDO.
	 */
	void HandlePreCompile(const FName& InPackageName);
	
	/** Helper method to return all referencers for a given package name */
	static void GetReferencers(const FName& InPackageName, TArray<FAssetDependency>& OutReferencers, TArray<FAssetData>& OutAssetsData);

	/** Helper method to return all referencers for a given package name */
	static void GetReferencers(const FName& InPackageName, TArray<FAssetDependency>& OutReferencers, TArray<FAssetData>& OutAssetsData, const TArray<UClass*>& InAllowedClasses);

	/** Filters the passed in FAssetDependency referencers returning only the one that are child class of filter class */
	static TArray<FAssetDependency> GetReferencersOfClass(const TArray<FAssetDependency>& InReferencers, const UClass* InFilterClass);
	
	/** Helper method to return all Gameplay Effect referencers for a given package name */
	static void GetGameplayEffectReferencers(const FName& InPackageName, TArray<FAssetDependency>& OutReferencers, TArray<FAssetData>& OutAssetsData);

	/** Tries to load UObject, checks if it is a gameplay effect and returns the CDO for that effect */
	static UGameplayEffect* GetGameplayEffectCDO(const FString& InPackageName);
	
	/** Tries to load UObject, checks if it is a gameplay effect and returns the CDO for that effect */
	static UGameplayEffect* GetGameplayEffectCDO(const FAssetDependency& InAssetDependency);

	/**
	 * From a package name (eg. /Game/Foo/Bar) returns the load path suitable to use with StaticLoadClass for a Blueprint load (eg. eg. /Game/Foo/Bar.Bar_C)
	 *
	 * Returns empty string if we were unable to format (eg. wasn't able to split on /)
	 */
	static FString GetLoadClassPackagePath(const FString& InPackageName);

	/** Handles update of all UK2Node_CallFunction nodes with Attribute Pin parameter to point to the new FGameplayAttribute that was renamed */
	void UpdateK2NodeReferencers(const FName& InPackageName, const FName& InOldPropertyName, const FName& InNewPropertyName);
	
	/** Gather the list of Blueprints with K2Node using a Pin Attribute parameter */
	TArray<FPinToModify> GetPinsToModify(const FString& InPackageName, const FString& InOldPropertyName, const FString& InNewPropertyName);

	/** Goes through the list of pins to modify, actually update the pin to point to the new attribute property name */
	void HandlePins(const TArray<FPinToModify>& InPinsToModify, const UBlueprint* InOwnerAttributeSetBP, const FName& InNewPropertyName);

	/** Bring focus and navigate to the token object */
	static void HandleMessageLogLinkActivated(const TSharedRef<IMessageToken>& InToken);

	/** Extracts attribute owner info from Pin Default value and returns it as a PackageName equivalent */
	static bool ParseAttributeFromDefaultValue(const FString& InDefaultValue, FString& OutPackageName, FString& OutAttributeName);
	
	/** Handles update of FGameplayAttribute properties in the referencers asset to point to the new FGameplayAttribute that was renamed */
	void UpdateReferencers(TArray<FAssetData> InReferencers, const FName& InPackageName, const FName& InOldPropertyName, const FName& InNewPropertyName);

	/**
	 * TODO: Probably not needed anymore since refactoring of Slate widget to use TWeakFieldPtr (that method was used to close any active / opened GE Blueprint to avoid a crash)
	 * Addendum: Still needed, if we have a ref to one of the attributes of a BP that is compiled, may crash (seen it consistently with Gameplay Cues Magnitude Attribute)
	 * Better TODO: See if we can "pause" the details customization (instead of closing / re-opening), or "refresh"
	 */
	void HandlePostCompile(const FName& InPackageName);
	
	/** Checks if given asset is currently being edited, and if so, closes the editor (required prior to file deletion) */
	static void CloseEditors(const TArray<FAssetData>& InAssets, TArray<FAssetData>& OutClosedAssets);
	
	/** Takes a list of package names to ask the Asset Editor subsystem to open */
	static void OpenClosedEditors(const TArray<FString>& InClosedAssets);
	
	/** Checks if given UObject asset is currently being edited by an Asset Editor (is it opened in editor right now?) */
	static bool IsAssetCurrentlyBeingEdited(const TSharedPtr<IToolkit>& InAssetEditor, const UObject* InAsset);

	/** Little timer delegate to delay re-opening of assets to the next frame (unused right now. TODO: check if still needed) */
	static void HandleNextTick(FName InPackageName, const TArray<FString> InClosedAssets);
};
