// License Copyright (c) 2024 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// Engine
#include "Engine/DataAsset.h"

// Auto-generated
#include "AssetBundlesCharacterData.generated.h"

/**
 * DataAsset to provide an example of how to use AssetBundles
 */
UCLASS()
class UAssetBundlesCharacterData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, meta=(AssetBundles="Lobby"))
	TSoftObjectPtr<UTexture2D> CharacterLobbyPortrait;

	UPROPERTY(EditDefaultsOnly)
	FText CharacterName;
	
	UPROPERTY(EditDefaultsOnly, meta=(AssetBundles="Game"))
	TSoftClassPtr<APawn> CharacterGamePawnClass;
	
protected:
	//~ Begin UObject Interface
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif
	//~ End UObject Interface
};
