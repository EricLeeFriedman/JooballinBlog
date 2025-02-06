// License Copyright (c) 2025 Eric Friedman

// Includes
// -------------------------------------
#include "TaskSequencingViewModel.h"

#include "Blueprint/UserWidget.h"
#include "MVVMGameSubsystem.h"
#include "TaskSequencingTargetViewModel.h"

/**
 * Task that simulates loading by waiting for a few seconds
 * Since the task completes at the end of the operator() call, it passes the TaskCompleteEvent
 * to the target ViewModel so  trigger when the color change is complete
 * Yellow = Loading
 * Green = Loaded
 */
struct FSimulateLoadingTask
{
	uint8 FakeLoadingTaskIndex = 0;
	TWeakObjectPtr<UTaskSequencingTargetViewModel> TargetViewModel;
	TSharedRef<UE::Tasks::FTaskEvent> TaskCompleteEvent = MakeShared<UE::Tasks::FTaskEvent>(UE_SOURCE_LOCATION);
	
	void operator()() const
	{
		TargetViewModel->SetLoadingTaskColor(FakeLoadingTaskIndex, FLinearColor::Yellow, nullptr);
		
		// Simulate loading a task by waiting for a few seconds
		FPlatformProcess::Sleep(FMath::RandRange(1.0f, 3.0f));

		TargetViewModel->SetLoadingTaskColor(FakeLoadingTaskIndex, FLinearColor::Green, TaskCompleteEvent);
	}
};

/**
 * Given a path and a controller, this task will client travel to another world
 * Since the task is complete at the end of the operator() call, OnTravelComplete is triggered
 * manually after the target world has been loaded and initialized so dependent tasks should use
 * the OnTravelComplete event as a prerequisite.
 */
struct FTravelToAnotherWorldTask
{
	FString TravelPath;
	TWeakObjectPtr<APlayerController> PlayerController;
	TSharedRef<UE::Tasks::FTaskEvent> OnTravelComplete = MakeShared<UE::Tasks::FTaskEvent>(UE_SOURCE_LOCATION);
	
	void operator()() const
	{
		// Simulate loading a larger world by waiting for a few seconds
		FPlatformProcess::Sleep(FMath::RandRange(0.5f, 4.0f));
		TSharedRef<UE::Tasks::FTaskEvent> OnTravelCompletePtr = OnTravelComplete;
		FWorldDelegates::OnPostWorldInitialization.AddLambda([OnTravelCompletePtr](UWorld*, FWorldInitializationValues)
		{
			OnTravelCompletePtr->Trigger();
		});
		PlayerController->ClientTravel(TravelPath, TRAVEL_Absolute);
	}
};

/**
 * Demonstrates a task that simulates loading by waiting for a few seconds
 * It calls back into the view model to update the loading task color
 * Yellow = Loading
 * Green = Loaded
 */
struct FDemonstrationLoadingTask
{
	uint8 TaskIndex = 0;
	TWeakObjectPtr<UTaskSequencingViewModel> TargetViewModel;
	
	void operator()() const
	{
		TargetViewModel->SetLoadingTaskColor(TaskIndex, FLinearColor::Yellow);
		FPlatformProcess::Sleep(FMath::RandRange(0.5f, 4.5f));
		TargetViewModel->SetLoadingTaskColor(TaskIndex, FLinearColor::Green);
	}
};

// SetLoadingTaskColor
// -------------------------------------
void UTaskSequencingViewModel::SetLoadingTaskColor(const uint8 TaskIndex, const FLinearColor& Color)
{
	AsyncTask(ENamedThreads::GameThread, [this, TaskIndex, Color]()
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
		case 3:
			UE_MVVM_SET_PROPERTY_VALUE(LoadingTask4Color, Color);
			break;
		default:
			check(false) // Invalid task index;
		}
	});
}

// TaskDemonstration
// -------------------------------------
void UTaskSequencingViewModel::TaskDemonstration()
{
	UE_MVVM_SET_PROPERTY_VALUE(LoadingTask1Color, FLinearColor::Red);
	UE_MVVM_SET_PROPERTY_VALUE(LoadingTask2Color, FLinearColor::Red);
	UE_MVVM_SET_PROPERTY_VALUE(LoadingTask3Color, FLinearColor::Red);
	UE_MVVM_SET_PROPERTY_VALUE(LoadingTask4Color, FLinearColor::Red);
	
	FDemonstrationLoadingTask LoadingTask1{0, this};
	FDemonstrationLoadingTask LoadingTask2{1, this};
	FDemonstrationLoadingTask LoadingTask3{2, this};
	FDemonstrationLoadingTask LoadingTask4{3, this};

	UE::Tasks::FTask Task1 = UE::Tasks::Launch(UE_SOURCE_LOCATION, MoveTemp(LoadingTask1));
	UE::Tasks::FTask Task2 = UE::Tasks::Launch(UE_SOURCE_LOCATION, MoveTemp(LoadingTask2), Task1);
	UE::Tasks::FTask Task3 = UE::Tasks::Launch(UE_SOURCE_LOCATION, MoveTemp(LoadingTask3), Task1);
	UE::Tasks::Launch(UE_SOURCE_LOCATION, MoveTemp(LoadingTask4), UE::Tasks::Prerequisites(Task2, Task3));
}

// TravelToAnotherWorld
// -------------------------------------
void UTaskSequencingViewModel::TravelToAnotherWorld()
{
	// Start the loading process by putting up a loading screen on the main thread
	UGameViewportClient* GameViewport = GetWorld()->GetGameViewport();
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	UUserWidget* LoadingScreen = CreateWidget(GameInstance, LoadingScreenWidgetClass);
	TSharedRef<SWidget> LoadingScreenWidget = LoadingScreen->TakeWidget();
	GameViewport->AddViewportWidgetContent(LoadingScreenWidget, 10.0f);
	
	// Travel to new world
	FTravelToAnotherWorldTask TravelTask;
	TravelTask.TravelPath = WorldToTravelTo.GetLongPackageName();
	TravelTask.PlayerController = GetWorld()->GetFirstPlayerController();
	UE::Tasks::Launch(UE_SOURCE_LOCATION, MoveTemp(TravelTask));

	// Create some fake loading tasks
	UMVVMGameSubsystem* MVVMSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>();
	UTaskSequencingTargetViewModel* TargetViewModel = Cast<UTaskSequencingTargetViewModel>(MVVMSubsystem->GetViewModelCollection()->FindFirstViewModelInstanceOfType(
		UTaskSequencingTargetViewModel::StaticClass()));
	
	FSimulateLoadingTask LoadingTask1{0, TargetViewModel};
	FSimulateLoadingTask LoadingTask2{1, TargetViewModel};
	FSimulateLoadingTask LoadingTask3{2, TargetViewModel};
	
	UE::Tasks::Launch(UE_SOURCE_LOCATION, MoveTemp(LoadingTask1), *TravelTask.OnTravelComplete);
	UE::Tasks::Launch(UE_SOURCE_LOCATION, MoveTemp(LoadingTask2), *TravelTask.OnTravelComplete);
	UE::Tasks::Launch(UE_SOURCE_LOCATION, MoveTemp(LoadingTask3), *TravelTask.OnTravelComplete);
	
	// Tear down loading screen
	UE::Tasks::Launch(UE_SOURCE_LOCATION, [LoadingScreenWidget, GameViewport]
	{
		AsyncTask(ENamedThreads::GameThread, [LoadingScreenWidget, GameViewport]()
		{
			GameViewport->RemoveViewportWidgetContent(LoadingScreenWidget);
		});
	}, UE::Tasks::Prerequisites(*LoadingTask1.TaskCompleteEvent, *LoadingTask2.TaskCompleteEvent, *LoadingTask3.TaskCompleteEvent));
}
