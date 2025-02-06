// License Copyright (c) 2025 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// Engine
#include "Subsystems/GameInstanceSubsystem.h"
#include "Types/MVVMViewModelContext.h"

// Auto-generated
#include "TaskSequencingGameSubsystem.generated.h"

// Forward Declarations
// -------------------------------------
class UMVVMViewModelCollectionObject;

/**
 * Creates a globally accessible ViewModel instance for the TaskSequencingTargetViewModel
 * to quicklu and easily demonstrate loading across multiple worlds
 */
UCLASS()
class UTaskSequencingGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UTaskSequencingGameSubsystem();
	
protected:
	//~ Begin USubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//~ End USubsystem Interface

private:
	FMVVMViewModelContext Context;
	TWeakObjectPtr<UMVVMViewModelCollectionObject> ViewModelCollection;
};
