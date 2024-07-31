// Copyright (c) 2023 Eric Friedman
 
#pragma once

// Includes
// -------------------------------------

// Engine
#include "Engine/DataAsset.h"

// Auto-generated
#include "DataValidationDataAsset.generated.h"

/**
 * Tutorial DataAsset for to demonstrate best practices for data validation.
 */
UCLASS()
class UDataValidationDataAsset final : public UDataAsset
{
	GENERATED_BODY()

public:
	/** A really important value */
	UPROPERTY(EditDefaultsOnly)
	int32 MyImportantValue = 0;

	/** How much to increase speed when asked */
	UPROPERTY(EditDefaultsOnly)
	float SpeedIncrease = 10.0f;

};
