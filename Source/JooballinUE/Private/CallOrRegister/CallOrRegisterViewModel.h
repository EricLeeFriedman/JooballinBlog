// License Copyright (c) 2025 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// Engine
#include "MVVMViewModelBase.h"

// Auto-generated
#include "CallOrRegisterViewModel.generated.h"

// Forward Declarations
// -------------------------------------
class ACallOrRegisterDemoActor;

/**
 * ViewModel to demonstrate the CallOrRegister pattern in action
 */
UCLASS()
class JOOBALLINUE_API UCallOrRegisterViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	// Begin MVVM Method Declarations
	// -------------------------------------
	UFUNCTION(BlueprintCallable)
	void SimpleEventSubscription();

	UFUNCTION(BlueprintCallable)
	void OutOfOrderEventSubscriptionBroken();

	UFUNCTION(BlueprintCallable)
	void OutOfOrderEventSubscriptionFixed();
	
	UFUNCTION(BlueprintCallable)
	void CallOrRegisterDemonstration();
	// -------------------------------------
	
private:
	void ResetStateAndSpawnDemoActor();
	
	// Begin MVVM Property Declarations
	// -------------------------------------
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	bool bCallback1Subscribed = false;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	bool bCallback1Complete = false;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	bool bCallback2Subscribed = false;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	bool bCallback2Complete = false;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	bool bActorBegunPlay = false;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	bool bDemonstrationRunning = false;
	// -------------------------------------
	
	UPROPERTY()
	TObjectPtr<ACallOrRegisterDemoActor> DemoActor;
};
