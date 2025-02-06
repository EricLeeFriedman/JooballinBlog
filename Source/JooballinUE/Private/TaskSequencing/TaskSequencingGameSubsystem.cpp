// License Copyright (c) 2025 Eric Friedman

// Includes
// -------------------------------------
#include "TaskSequencingGameSubsystem.h"

#include "MVVMGameSubsystem.h"
#include "TaskSequencingTargetViewModel.h"

// CONSTRUCTOR
// -------------------------------------
UTaskSequencingGameSubsystem::UTaskSequencingGameSubsystem()
{
	Context.ContextClass = UTaskSequencingTargetViewModel::StaticClass();
	Context.ContextName = TEXT("TaskSequencingTargetViewModel");
}

// Initialize
// -------------------------------------
/*virtual*/ void UTaskSequencingGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UMVVMGameSubsystem* MVVMSubsystem = Collection.InitializeDependency<UMVVMGameSubsystem>();
	ViewModelCollection = MVVMSubsystem->GetViewModelCollection();
	check(ViewModelCollection.IsValid());
	ViewModelCollection->AddViewModelInstance(Context, NewObject<UTaskSequencingTargetViewModel>());
}

// Deinitialize
// -------------------------------------
/*virtual*/ void UTaskSequencingGameSubsystem::Deinitialize()
{
	if (UMVVMViewModelCollectionObject* ViewModelCollectionPtr = ViewModelCollection.Get())
	{
		ViewModelCollectionPtr->RemoveViewModel(Context);
	}
	Super::Deinitialize();
}
