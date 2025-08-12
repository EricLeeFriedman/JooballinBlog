// License Copyright (c) 2025 Eric Friedman

// Includes
// -------------------------------------
#include "CallOrRegisterViewModel.h"

// JooballinUE
#include "CallOrRegisterDemoActor.h"

// SimpleEventSubscription
// -------------------------------------
void UCallOrRegisterViewModel::SimpleEventSubscription()
{
	ResetStateAndSpawnDemoActor();

	// Callback 1
	DemoActor->OnBeginPlay.AddLambda([this]()
	{
		UE_MVVM_SET_PROPERTY_VALUE(bCallback1Complete, true);
	});
	UE_MVVM_SET_PROPERTY_VALUE(bCallback1Subscribed, true);

	// Callback 2
	DemoActor->OnBeginPlay.AddLambda([this]()
	{
		UE_MVVM_SET_PROPERTY_VALUE(bCallback2Complete, true);
	});
	UE_MVVM_SET_PROPERTY_VALUE(bCallback2Subscribed, true);

	// Actor Begun Play
	DemoActor->OnBeginPlay.AddLambda([this]()
	{
		UE_MVVM_SET_PROPERTY_VALUE(bActorBegunPlay, true);
		UE_MVVM_SET_PROPERTY_VALUE(bDemonstrationRunning, false);
	});
	
	DemoActor->FinishSpawning(FTransform::Identity);
}

// OutOfOrderEventSubscriptionBroken
// -------------------------------------
void UCallOrRegisterViewModel::OutOfOrderEventSubscriptionBroken()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	ResetStateAndSpawnDemoActor();

	// Callback 1
	DemoActor->OnBeginPlay.AddLambda([this]()
	{
		UE_MVVM_SET_PROPERTY_VALUE(bCallback1Complete, true);
	});
	UE_MVVM_SET_PROPERTY_VALUE(bCallback1Subscribed, true);

	// Callback 2
	FTimerHandle Callback2Handle;
	TimerManager.SetTimer(Callback2Handle, [this]()
	{
		DemoActor->OnBeginPlay.AddLambda([this]()
		{
			UE_MVVM_SET_PROPERTY_VALUE(bCallback2Complete, true);
		});
		UE_MVVM_SET_PROPERTY_VALUE(bCallback2Subscribed, true);
		UE_MVVM_SET_PROPERTY_VALUE(bDemonstrationRunning, false);
	}, 2.0f, false);

	// Actor Begun Play
	DemoActor->OnBeginPlay.AddLambda([this]()
	{
		UE_MVVM_SET_PROPERTY_VALUE(bActorBegunPlay, true);
	});

	FTimerHandle FinishSpawningHandle;
	TimerManager.SetTimer(FinishSpawningHandle, [this]()
	{
		DemoActor->FinishSpawning(FTransform::Identity);
	}, 1.0f, false);
}

// OutOfOrderEventSubscriptionFixed
// -------------------------------------
void UCallOrRegisterViewModel::OutOfOrderEventSubscriptionFixed()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	ResetStateAndSpawnDemoActor();

	// Callback 1
	if (DemoActor->HasActorBegunPlay())
	{
		UE_MVVM_SET_PROPERTY_VALUE(bCallback1Complete, true);
	}
	else
	{
		DemoActor->OnBeginPlay.AddLambda([this]()
		{
			UE_MVVM_SET_PROPERTY_VALUE(bCallback1Complete, true);
		});
	}
	UE_MVVM_SET_PROPERTY_VALUE(bCallback1Subscribed, true);

	// Callback 2
	FTimerHandle Callback2Handle;
	TimerManager.SetTimer(Callback2Handle, [this]()
	{
		if (DemoActor->HasActorBegunPlay())
		{
			UE_MVVM_SET_PROPERTY_VALUE(bCallback2Complete, true);
		}
		else
		{
			DemoActor->OnBeginPlay.AddLambda([this]()
			{
				UE_MVVM_SET_PROPERTY_VALUE(bCallback2Complete, true);
			});	
		}
		UE_MVVM_SET_PROPERTY_VALUE(bCallback2Subscribed, true);
		UE_MVVM_SET_PROPERTY_VALUE(bDemonstrationRunning, false);
	}, 2.0f, false);

	// Actor Begun Play
	if (DemoActor->HasActorBegunPlay())
	{
		UE_MVVM_SET_PROPERTY_VALUE(bActorBegunPlay, true);
	}
	else
	{
		DemoActor->OnBeginPlay.AddLambda([this]()
		{
			UE_MVVM_SET_PROPERTY_VALUE(bActorBegunPlay, true);
		});
	}

	FTimerHandle FinishSpawningHandle;
	TimerManager.SetTimer(FinishSpawningHandle, [this]()
	{
		DemoActor->FinishSpawning(FTransform::Identity);
	}, 1.0f, false);
}

// CallOrRegisterDemonstration
// -------------------------------------
void UCallOrRegisterViewModel::CallOrRegisterDemonstration()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	ResetStateAndSpawnDemoActor();

	// Callback 1
	DemoActor->CallOrRegister_OnBeginPlay(FSimpleMulticastDelegate::FDelegate::CreateLambda([this]()
	{
		UE_MVVM_SET_PROPERTY_VALUE(bCallback1Complete, true);
	}));
	UE_MVVM_SET_PROPERTY_VALUE(bCallback1Subscribed, true);

	// Callback 2
	FTimerHandle Callback2Handle;;
	TimerManager.SetTimer(Callback2Handle, [this]()
	{
		DemoActor->CallOrRegister_OnBeginPlay(FSimpleMulticastDelegate::FDelegate::CreateLambda([this]()
		{
			UE_MVVM_SET_PROPERTY_VALUE(bCallback2Complete, true);
		}));
		UE_MVVM_SET_PROPERTY_VALUE(bCallback2Subscribed, true);
		UE_MVVM_SET_PROPERTY_VALUE(bDemonstrationRunning, false);
	}, 2.0f, false);

	// Actor Begun Play
	DemoActor->CallOrRegister_OnBeginPlay(FSimpleMulticastDelegate::FDelegate::CreateLambda([this]()
	{
		UE_MVVM_SET_PROPERTY_VALUE(bActorBegunPlay, true);
	}));

	FTimerHandle FinishSpawningHandle;
	TimerManager.SetTimer(FinishSpawningHandle, [this]()
	{
		DemoActor->FinishSpawning(FTransform::Identity);
	}, 1.0f, false);
}

// ResetStateAndSpawnDemoActor
// -------------------------------------
void UCallOrRegisterViewModel::ResetStateAndSpawnDemoActor()
{
	UE_MVVM_SET_PROPERTY_VALUE(bCallback1Subscribed, false);
	UE_MVVM_SET_PROPERTY_VALUE(bCallback1Complete, false);
	UE_MVVM_SET_PROPERTY_VALUE(bCallback2Subscribed, false);
	UE_MVVM_SET_PROPERTY_VALUE(bCallback2Complete, false);
	UE_MVVM_SET_PROPERTY_VALUE(bActorBegunPlay, false);
	UE_MVVM_SET_PROPERTY_VALUE(bDemonstrationRunning, true);

	if (DemoActor) 
	{
		DemoActor->Destroy();
		DemoActor = nullptr;
	}
	
	DemoActor = GetWorld()->SpawnActorDeferred<ACallOrRegisterDemoActor>(
		ACallOrRegisterDemoActor::StaticClass(),
		FTransform::Identity);
}
