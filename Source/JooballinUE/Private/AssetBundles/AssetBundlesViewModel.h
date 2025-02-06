// License Copyright (c) 2025 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// Engine
#include "MVVMViewModelBase.h"

// Auto-generated
#include "AssetBundlesViewModel.generated.h"

// Forward Declarations
// -------------------------------------
class UAssetBundlesCharacterData;
struct FStreamableHandle;

/**
 * ViewModel that handles loading and displaying character data with asset bundles.
 */
UCLASS()
class JOOBALLINUE_API UAssetBundlesViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UAssetBundlesViewModel();
	
	// Begin MVVM Method Declarations
	// -------------------------------------
	UFUNCTION(BlueprintCallable)
	void ClearCharacterData();
	
	UFUNCTION(BlueprintCallable)
	void LoadWithoutAssetBundles();

	UFUNCTION(BlueprintCallable)
	void LoadWithGameAssetBundle();

	UFUNCTION(BlueprintCallable)
	void LoadWithLobbyAssetBundle();

	UFUNCTION(BlueprintCallable)
	void LoadWithGameAndLobbyAssetBundles();
	// -------------------------------------

private:
	void LoadCharacterDataInternal(const TArray<FName>& AssetBundles);
	TSharedPtr<FStreamableHandle> CharacterDataHandle;
	const FPrimaryAssetType PrimaryAssetType;
	
	// Begin MVVM Property Declarations
	// -------------------------------------
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	TObjectPtr<UTexture2D> CharacterLobbyPortrait;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	FText CharacterName;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	FText GamePawnClassName;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	bool bAssetBundlesLoaded = false;
	// -------------------------------------
};
