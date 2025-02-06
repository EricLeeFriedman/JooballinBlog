// License Copyright (c) 2025 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// Engine
#include "MVVMViewModelBase.h"

// Auto-generated
#include "TaskSequencingTargetViewModel.generated.h"

/**
 * ViewModel for the target world in the Travel To Another World task example
 */
UCLASS()
class UTaskSequencingTargetViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:
	void SetLoadingTaskColor(const uint8 TaskIndex, const FLinearColor& Color, TSharedPtr<UE::Tasks::FTaskEvent> TaskCompleteEvent);
	
private:
	// Begin MVVM Property Declarations
	// -------------------------------------
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	FLinearColor LoadingTask1Color;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	FLinearColor LoadingTask2Color;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	FLinearColor LoadingTask3Color;
	// -------------------------------------
};
