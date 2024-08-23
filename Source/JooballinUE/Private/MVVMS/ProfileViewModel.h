// License Copyright (c) 2024 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// Engine
#include "MVVMViewModelBase.h"

// Auto-generated
#include "ProfileViewModel.generated.h"

/**
 * ViewModel to demonstrate using a service to load a user profile.
 */
UCLASS()
class UProfileViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	// Begin MVVM Method Declarations
	// -------------------------------------
	UFUNCTION(BlueprintCallable)
	void LoadProfile();
	// -------------------------------------
	
private:
	// Begin MVVM Property Declarations
	// -------------------------------------
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	FText Name;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	int32 Age = 0;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	FString Website;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	bool bIsProfileLoading = false;
	// -------------------------------------
};
