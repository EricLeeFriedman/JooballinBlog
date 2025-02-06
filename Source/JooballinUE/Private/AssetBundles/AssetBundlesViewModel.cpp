// License Copyright (c) 2025 Eric Friedman

// Includes
// -------------------------------------
#include "AssetBundlesViewModel.h"

// JooballinUE
#include "Engine/AssetManager.h"

// Engine
#include "AssetBundlesCharacterData.h"

// CONSTRUCTOR
// -------------------------------------
UAssetBundlesViewModel::UAssetBundlesViewModel()
	: PrimaryAssetType(UAssetBundlesCharacterData::StaticClass()->GetFName())
{
}

// ClearCharacterData
// -------------------------------------
void UAssetBundlesViewModel::ClearCharacterData()
{
	if (CharacterDataHandle)
	{
		CharacterDataHandle->ReleaseHandle();
		CharacterDataHandle.Reset();
	}
	UE_MVVM_SET_PROPERTY_VALUE(bAssetBundlesLoaded, false);
	UE_MVVM_SET_PROPERTY_VALUE(CharacterLobbyPortrait, nullptr);
	UE_MVVM_SET_PROPERTY_VALUE(CharacterName, FText::GetEmpty());
	UE_MVVM_SET_PROPERTY_VALUE(GamePawnClassName, FText::GetEmpty());
	GEngine->ForceGarbageCollection();
}

// LoadCharacterData
// -------------------------------------
void UAssetBundlesViewModel::LoadWithoutAssetBundles()
{
	LoadCharacterDataInternal({});
}

// LoadWithGameAssetBundle
// -------------------------------------
void UAssetBundlesViewModel::LoadWithGameAssetBundle()
{
	LoadCharacterDataInternal({ "Game" });
}

// LoadWithLobbyAssetBundle
// -------------------------------------
void UAssetBundlesViewModel::LoadWithLobbyAssetBundle()
{
	LoadCharacterDataInternal({ "Lobby" });
}

// LoadWithGameAndLobbyAssetBundles
// -------------------------------------
void UAssetBundlesViewModel::LoadWithGameAndLobbyAssetBundles()
{
	LoadCharacterDataInternal({ "Game", "Lobby" });
}

// LoadCharacterDataInternal
// -------------------------------------
void UAssetBundlesViewModel::LoadCharacterDataInternal(const TArray<FName>& AssetBundles)
{
	UE_MVVM_SET_PROPERTY_VALUE(bAssetBundlesLoaded, true);

	UAssetManager& AssetManager = UAssetManager::Get();
	CharacterDataHandle = AssetManager.LoadPrimaryAssetsWithType(
		PrimaryAssetType, AssetBundles,
		FStreamableDelegate::CreateLambda([this]()
		{
			TArray<FPrimaryAssetId> AssetIds;
			UAssetManager::Get().GetPrimaryAssetIdList(UAssetBundlesCharacterData::StaticClass()->GetFName(), AssetIds);
			if (const UAssetBundlesCharacterData* LoadedAsset = Cast<UAssetBundlesCharacterData>(
				UAssetManager::Get().GetPrimaryAssetObject(AssetIds[0])))
			{
				const FText GamePawnClassNameText = LoadedAsset->CharacterGamePawnClass ?
					FText::FromString(LoadedAsset->CharacterGamePawnClass->GetName())
					: FText::GetEmpty();
				
				UE_MVVM_SET_PROPERTY_VALUE(CharacterLobbyPortrait, LoadedAsset->CharacterLobbyPortrait.Get());
				UE_MVVM_SET_PROPERTY_VALUE(CharacterName, LoadedAsset->CharacterName);
				UE_MVVM_SET_PROPERTY_VALUE(GamePawnClassName, GamePawnClassNameText);
			}
		}));
}
