// Copyright (c) 2023 Eric Friedman

// Includes
// -------------------------------------
#include "DataValidation/DataValidationActor.h"

// JooballinUE
#include "DataValidation/DataValidationDataAsset.h"

// Engine
#include "Misc/DataValidation.h"

// GetDataAsset
// -------------------------------------
const UDataValidationDataAsset& ADataValidationActor::GetDataAsset() const
{
    return *DataAsset;
}

// IncreaseSpeed
// -------------------------------------
void ADataValidationActor::IncreaseSpeed()
{
    MySpeed += DataAsset->SpeedIncrease;   
}

// BeginPlay
// -------------------------------------
/*virtual*/void ADataValidationActor::BeginPlay()
{
    Super::BeginPlay();
    MyVeryImportantValue = DataAsset->MyImportantValue;
}

#if WITH_EDITOR
// IsDataValid
// -------------------------------------
/*virtual*/ EDataValidationResult ADataValidationActor::IsDataValid(FDataValidationContext& Context) const
{
    EDataValidationResult Result = Super::IsDataValid(Context);
    if (!DataAsset)
    {
        Context.AddError(INVTEXT("DataAsset is null!"));
        Result = EDataValidationResult::Invalid;
    }
    return Result;
}
#endif // WITH_EDITOR
