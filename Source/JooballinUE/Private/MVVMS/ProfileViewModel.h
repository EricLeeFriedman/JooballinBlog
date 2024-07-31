// License Copyright (c) 2024 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// Engine
#include "MVVMViewModelBase.h"

// Auto-generated
#include "ProfileViewModel.generated.h"

// Forward Declarations
// -------------------------------------
class IProfileService;

/**
 * 
 */
UCLASS()
class JOOBALLINUE_API UProfileViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UProfileViewModel();
	explicit UProfileViewModel(FVTableHelper& Helper);
	virtual ~UProfileViewModel() override;

	// Begin MVVM Method Declarations
	// -------------------------------------
	UFUNCTION(BlueprintCallable)
	void LoadProfile();
	// -------------------------------------
	
private:
	TSharedRef<IProfileService> ProfileService;

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
