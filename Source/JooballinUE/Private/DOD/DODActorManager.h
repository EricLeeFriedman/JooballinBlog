// License Copyright (c) 2024 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// JooballinUE
#include "DODTickMode.h"

// Engine
#include "GameFramework/Actor.h"

// Auto-generated
#include "DODActorManager.generated.h"

// Forward Declarations
// -------------------------------------
class ADODActor;

/**
 * Spawns a number of DOD actors.
 * Handles a few different tick modes:
 *	- Actor: Each actor ticks individually
 *	- Manager: The manager ticks and updates the actors
 *	- ManagerData: The manager ticks and updates the actors based on data stored in the manager
 */
UCLASS()
class JOOBALLINUE_API ADODActorManager : public AActor
{
	GENERATED_BODY()

public:
	ADODActorManager();
	void SetTickMode(const EDODTickMode InDODTickMode);
	
protected:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ End AActor Interface

	//~ Begin UObject Interface
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif // WITH_EDITOR
	//~ End UObject Interface
	
private:
	void TickActors(const float DeltaTime);
	void TickManagerData(const float DeltaTime);
	
	UPROPERTY(Transient)
	TArray<TObjectPtr<ADODActor>> SpawnedActors;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ADODActor> ActorClass;

	EDODTickMode DODTickMode = EDODTickMode::Actor;
	
	struct FActorData
	{
		float UpdateZ = 0.0f;
		FVector ActorLocation;
	};
	
	constexpr static int32 NumActorColumns = 100;
	constexpr static int32 NumActorRows = 100;
	constexpr static int32 NumActors = NumActorColumns * NumActorRows;
	TStaticArray<FActorData, NumActors> ManagerActorData;
};
