// License Copyright (c) 2025 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// Engine
#include "UObject/Object.h"

// Auto-generated
#include "CallOrRegisterDemoActor.generated.h"

/**
 * Demo object that will be used to demonstrate the CallOrRegister pattern
 */
UCLASS()
class JOOBALLINUE_API ACallOrRegisterDemoActor : public AActor
{
	GENERATED_BODY()

public:
	void CallOrRegister_OnBeginPlay(FSimpleMulticastDelegate::FDelegate&& Delegate);
	
	FSimpleMulticastDelegate OnBeginPlay;
	
protected:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	//~ End AActor Interface
};
