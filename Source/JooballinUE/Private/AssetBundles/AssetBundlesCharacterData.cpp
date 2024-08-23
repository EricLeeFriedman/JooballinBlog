// License Copyright (c) 2024 Eric Friedman

// Includes
// -------------------------------------
#include "AssetBundlesCharacterData.h"

// Engine
#include "Misc/DataValidation.h"

#if WITH_EDITOR
// IsDataValid
// -------------------------------------
/*virtual*/ EDataValidationResult UAssetBundlesCharacterData::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);
	if (!CharacterLobbyPortrait.IsPending())
	{
		Context.AddError(INVTEXT("CharacterLobbyPortrait is required"));
		Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
	}
	if (!CharacterGamePawnClass)
	{
		Context.AddError(INVTEXT("CharacterGamePawnClass is required"));
		Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
	}
	return Result;
}
#endif
