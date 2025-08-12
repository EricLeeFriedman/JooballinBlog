// License Copyright (c) 2025 Eric Friedman

// Includes
// -------------------------------------
#include "CallOrRegisterDemoActor.h"

// CallOrRegister_OnBeginPlay
// -------------------------------------
void ACallOrRegisterDemoActor::CallOrRegister_OnBeginPlay(FSimpleMulticastDelegate::FDelegate&& Delegate)
{
	if (HasActorBegunPlay())
	{
		Delegate.ExecuteIfBound();
	}
	else
	{
		OnBeginPlay.Add(MoveTemp(Delegate));
	}
}

// BeginPlay
// -------------------------------------
/*virtual*/ void ACallOrRegisterDemoActor::BeginPlay()
{
	Super::BeginPlay();
	OnBeginPlay.Broadcast();
	OnBeginPlay.Clear();
}
