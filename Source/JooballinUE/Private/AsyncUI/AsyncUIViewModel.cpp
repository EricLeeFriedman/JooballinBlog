// License Copyright (c) 2025 Eric Friedman

// Includes
// -------------------------------------
#include "AsyncUIViewModel.h"

// DoALongRunningTask
// -------------------------------------
void UAsyncUIViewModel::DoALongRunningTask()
{
	FPlatformProcess::Sleep(3.0f);
	UE_MVVM_SET_PROPERTY_VALUE(RunCount, RunCount + 1);
}

