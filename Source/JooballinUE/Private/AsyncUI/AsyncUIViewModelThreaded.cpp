// License Copyright (c) 2024 Eric Friedman

// Includes
// -------------------------------------
#include "AsyncUIViewModelThreaded.h"

// DoALongRunningAsyncTask
// -------------------------------------
void UAsyncUIViewModelThreaded::DoALongRunningAsyncTask()
{
	UE_MVVM_SET_PROPERTY_VALUE(bIsTaskRunning, true);
	
	DoALongRunningAsyncTaskInternal().Next([this](const int32 Result)
	{
		// Execute UI changes back on the game thread
		AsyncTask(ENamedThreads::GameThread, [this, Result]()
		{
			UE_MVVM_SET_PROPERTY_VALUE(bIsTaskRunning, false);
			UE_MVVM_SET_PROPERTY_VALUE(RunCount, Result);
		});
	});
}

// DoALongRunningAsyncTaskInternal
// -------------------------------------
TFuture<int32> UAsyncUIViewModelThreaded::DoALongRunningAsyncTaskInternal()
{
	TSharedRef<TPromise<int32>> Promise = MakeShared<TPromise<int32>>();
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, Promise]()
	{
		FPlatformProcess::Sleep(3.0f);
		Promise->SetValue(RunCount + 1);
	});
	return Promise->GetFuture();
}