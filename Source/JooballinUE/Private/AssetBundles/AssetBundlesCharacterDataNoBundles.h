// License Copyright (c) 2024 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// Engine
#include "Engine/DataAsset.h"

// Auto-generated
#include "AssetBundlesCharacterDataNoBundles.generated.h"

/**
 * Example DataAsset that does not use asset bundles.
 */
UCLASS()
class UAssetBundlesCharacterDataNoBundles : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> CharacterLobbyPortrait;

	UPROPERTY(EditDefaultsOnly)
	FText CharacterName;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> CharacterGamePawnClass;
};
