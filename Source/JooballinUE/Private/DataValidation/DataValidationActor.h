// Copyright (c) 2023 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// Engine
#include "GameFramework/Actor.h"

// Auto-generated
#include "DataValidationActor.generated.h"

// Forward Declarations
// -------------------------------------
class UDataValidationDataAsset;

/**
 * Tutorial Actor for to demonstrate best practices for data validation.
 */
UCLASS(Abstract)
class ADataValidationActor : public AActor
{
    GENERATED_BODY()

public:
    const UDataValidationDataAsset& GetDataAsset() const;

    void IncreaseSpeed();

protected:
    //~ Begin AActor Interface
    virtual void BeginPlay() override;
    //~ End AActor Interface

    //~ Begin UObject Interface
#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif // WITH_EDITOR
    //~ End UObject Interface

private:
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UDataValidationDataAsset> DataAsset;

    int32 MyVeryImportantValue = 0;
    float MySpeed = 5.0f;
};
