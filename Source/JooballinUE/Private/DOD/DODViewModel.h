// License Copyright (c) 2024 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// Engine
#include "MVVMViewModelBase.h"

// Auto-generated
#include "DODViewModel.generated.h"

// Forward Declarations
// -------------------------------------
enum class EDODTickMode : uint8;

/**
 * ViewModel that switches the tick mode of the DOD actors.
 */
UCLASS()
class JOOBALLINUE_API UDODViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	// Begin MVVM Method Declarations
	// -------------------------------------
	UFUNCTION(BlueprintCallable)
	void SetDODTickMode(const EDODTickMode InDODTickMode);
	// -------------------------------------
};
