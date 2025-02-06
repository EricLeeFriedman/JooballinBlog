// License Copyright (c) 2025 Eric Friedman

// Includes
// -------------------------------------
#include "DODActorManager.h"

// JooballinUE
#include "DODActor.h"
#include "DODConstants.h"

// Engine
#include "Misc/DataValidation.h"

// CONSTRUCTOR
// -------------------------------------
ADODActorManager::ADODActorManager()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = DODTickMode != EDODTickMode::Actor;
}

// SetTickMode
// -------------------------------------
void ADODActorManager::SetTickMode(const EDODTickMode InDODTickMode)
{
	if (DODTickMode == InDODTickMode) return;
	DODTickMode = InDODTickMode;

	// Enable/Disable the tick of the manager based on the tick mode
	const bool bThisTickEnabled = InDODTickMode != EDODTickMode::Actor;
	SetActorTickEnabled(bThisTickEnabled);

	// Enable/Disable the tick of the spawned actors based on the tick mode
	const bool bActorTickEnabled = !bThisTickEnabled;
	for (const TObjectPtr<ADODActor>& Actor : SpawnedActors)
	{
		Actor->SetActorTickEnabled(bActorTickEnabled);
	}

	// If going to ManagerData update the data from the spawned actors
	if (DODTickMode == EDODTickMode::ManagerData)
	{
		check(SpawnedActors.Num() == ManagerActorData.Num())
		for (int32 Index = 0; Index < ManagerActorData.Num(); ++Index)
		{
			ManagerActorData[Index].ActorLocation = SpawnedActors[Index]->GetActorLocation();
			ManagerActorData[Index].UpdateZ = SpawnedActors[Index]->UpdateZ;
		}
	}
	
}

// BeginPlay
// -------------------------------------
/*virtual*/ void ADODActorManager::BeginPlay()
{
	Super::BeginPlay();

	// Disable occlusion queries for this example
	// Since we are moving the meshes in the shader, this prevents occlusion culling from causing the meshes to disappear
	GEngine->Exec(GetWorld(), TEXT("r.AllowOcclusionQueries 0"));

	// Spawn the actors in a grid
	const bool bActorTickEnabled = DODTickMode == EDODTickMode::Actor;
	SpawnedActors.Reserve(NumActors);
	for (int32 Row = -(NumActorRows / 2); Row < (NumActorRows / 2); ++Row)
	{
		for (int32 Col = -(NumActorColumns / 2); Col < (NumActorColumns / 2); ++Col)
		{
			constexpr float Spacing = 150.0f;
			const FVector Location = FVector(Row * Spacing, Col * Spacing, 0.0f);
			ADODActor* Actor = GetWorld()->SpawnActor<ADODActor>(ActorClass, FTransform(Location));

			Actor->SetActorTickEnabled(bActorTickEnabled);

			SpawnedActors.Push(Actor);
		}
	}
}

// Tick
// -------------------------------------
/*virtual*/ void ADODActorManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (DODTickMode)
	{
	case EDODTickMode::ActorByManager:
		TickActors(DeltaSeconds);
		break;
	case EDODTickMode::ManagerData:
		TickManagerData(DeltaSeconds);
		break;
	default:
		ensureMsgf(false, TEXT("Unhandled DODTickMode: %s"), *UEnum::GetValueAsString(DODTickMode));
		break;
	}
}

// EndPlay
// -------------------------------------
/*virtual*/ void ADODActorManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GEngine->Exec(GetWorld(), TEXT("r.AllowOcclusionQueries 1"));
	Super::EndPlay(EndPlayReason);
}

#if WITH_EDITOR
// IsDataValid
// -------------------------------------
/*virtual*/ EDataValidationResult ADODActorManager::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);
	if (!ActorClass)
	{
		Context.AddError(INVTEXT("ActorClass must be set."));
		Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
	}
	return Result;
}
#endif // WITH_EDITOR

// TickActors
// -------------------------------------
void ADODActorManager::TickActors(const float DeltaTime)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(ADODActorManager::TickActors);
	
	for (const TObjectPtr<ADODActor>& Actor : SpawnedActors)
	{
		Actor->UpdateMesh(DeltaTime);
	}
}

// TickManagerData
// -------------------------------------
void ADODActorManager::TickManagerData(const float DeltaTime)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(ADODActorManager::TickManagerData);
	check(SpawnedActors.Num() == ManagerActorData.Num())
	
	const FVector CameraLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
	
	for (int32 Index = 0; Index < NumActors; ++Index)
	{
		FActorData& ActorData = ManagerActorData[Index];

		// Bounce the mesh up and down
		ActorData.UpdateZ += (DeltaTime * DODConstants::ZMovementSpeed);
		const float CosNormalized = (FMath::Cos(ActorData.UpdateZ) + 1.0f) / 2.0f;
		const float ZOffset = FMath::Lerp(0.0f, DODConstants::MaxHeight, CosNormalized);

		// Color the mesh based on distance from camera
		const float Distance = FVector::Dist(CameraLocation, ActorData.ActorLocation);
		const float RedValue = FMath::Clamp(Distance / DODConstants::RedDistance, 0.0f, 1.0f);

		SpawnedActors[Index]->MaterialInstance->SetScalarParameterValue("ZOffset", ZOffset);
		SpawnedActors[Index]->MaterialInstance->SetScalarParameterValue("RedValue", RedValue);
	}
}
