// License Copyright (c) 2025 Eric Friedman

// Includes
// -------------------------------------
#include "TaskSequencingTargetViewModel.h"

// SetLoadingTaskColor
// -------------------------------------
void UTaskSequencingTargetViewModel::SetLoadingTaskColor(const uint8 TaskIndex, const FLinearColor& Color, TSharedPtr<UE::Tasks::FTaskEvent> TaskCompleteEvent)
{
	AsyncTask(ENamedThreads::GameThread, [this, TaskIndex, Color, TaskCompleteEvent]()
	{
		switch (TaskIndex)
		{
		case 0:
			UE_MVVM_SET_PROPERTY_VALUE(LoadingTask1Color, Color);
			break;
		case 1:
			UE_MVVM_SET_PROPERTY_VALUE(LoadingTask2Color, Color);
			break;
		case 2:
			UE_MVVM_SET_PROPERTY_VALUE(LoadingTask3Color, Color);
			break;
		default:
			check(false);
		}
		
		if (TaskCompleteEvent)
		{
			TaskCompleteEvent->Trigger();
		}
	});
}
