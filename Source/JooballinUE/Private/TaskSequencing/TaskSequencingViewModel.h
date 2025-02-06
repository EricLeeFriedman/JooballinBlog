// License Copyright (c) 2025 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// Engine
#include "MVVMViewModelBase.h"

// Auto-generated
#include "TaskSequencingViewModel.generated.h"

// Forward Declarations
// -------------------------------------
class UUserWidget;

/**
 * ViewModel that will demonstrate visually how task dependencies can be sequenced
 * Also handles creating a sequence of tasks that load into another world with a loading screen
 */
UCLASS()
class UTaskSequencingViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void SetLoadingTaskColor(const uint8 TaskIndex, const FLinearColor& Color);

	// Begin MVVM Method Declarations
	// -------------------------------------
	UFUNCTION(BlueprintCallable)
	void TaskDemonstration();
	
	UFUNCTION(BlueprintCallable)
	void TravelToAnotherWorld();
	// -------------------------------------

private:
	// Begin MVVM Property Declarations
	// -------------------------------------
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	FLinearColor LoadingTask1Color = FLinearColor::Red;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	FLinearColor LoadingTask2Color = FLinearColor::Red;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	FLinearColor LoadingTask3Color = FLinearColor::Red;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	FLinearColor LoadingTask4Color = FLinearColor::Red;
	// -------------------------------------
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoadingScreenWidgetClass;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> WorldToTravelTo;
};
