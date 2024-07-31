// License Copyright (c) 2024 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// Engine
#include "MVVMViewModelBase.h"

// Auto-generated
#include "AsyncUIViewModelThreaded.generated.h"

/**
 * View model that does a long task on a background thread
 */
UCLASS()
class UAsyncUIViewModelThreaded : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	// Begin MVVM Method Declarations
	// -------------------------------------
	UFUNCTION(BlueprintCallable)
	void DoALongRunningAsyncTask();
	// -------------------------------------
	
private:
	TFuture<int32> DoALongRunningAsyncTaskInternal();
	
	// Begin MVVM Property Declarations
	// -------------------------------------
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	int32 RunCount = 0;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	bool bIsTaskRunning = false;
	// -------------------------------------
};
