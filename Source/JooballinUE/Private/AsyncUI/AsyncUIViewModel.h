// License Copyright (c) 2025 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// Engine
#include "MVVMViewModelBase.h"

// Auto-generated
#include "AsyncUIViewModel.generated.h"

/**
 * View model that does a long task on the game thread
 */
UCLASS()
class UAsyncUIViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	// Begin MVVM Method Declarations
	// -------------------------------------
	UFUNCTION(BlueprintCallable)
	void DoALongRunningTask();
	// -------------------------------------

private:

	// Begin MVVM Property Declarations
	// -------------------------------------
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	int32 RunCount = 0;
	// -------------------------------------
};
