// License Copyright (c) 2025 Eric Friedman

// Includes
// -------------------------------------
#include "DODActor.h"

// JooballinUE
#include "DODConstants.h"

// CONSTRUCTOR
// -------------------------------------
ADODActor::ADODActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->PrimaryComponentTick.bCanEverTick = false;
	RootComponent = MeshComponent;
}

// UpdateMesh
// -------------------------------------
void ADODActor::UpdateMesh(const float DeltaTime)
{
	const FVector CameraLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
	const FVector ActorLocation = GetActorLocation();

	// Bounce the mesh up and down
	UpdateZ += (DeltaTime * DODConstants::ZMovementSpeed);
	const float CosNormalized = (FMath::Cos(UpdateZ) + 1.0f) / 2.0f;
	const float ZOffset = FMath::Lerp(0.0f, DODConstants::MaxHeight, CosNormalized);
	MaterialInstance->SetScalarParameterValue("ZOffset", ZOffset);

	// Color the mesh based on distance from camera
	const float Distance = FVector::Dist(CameraLocation, ActorLocation);
	const float RedValue = FMath::Clamp(Distance / DODConstants::RedDistance, 0.0f, 1.0f);
	MaterialInstance->SetScalarParameterValue("RedValue", RedValue);
}

// BeginPlay
// -------------------------------------
/*virtual*/ void ADODActor::BeginPlay()
{
	Super::BeginPlay();
	UpdateZ = FMath::RandRange(0.0f, 999.0f);
	MaterialInstance = UMaterialInstanceDynamic::Create(Material, this);
	MeshComponent->SetMaterial(0, MaterialInstance);
}

// Tick
// -------------------------------------
/*virtual*/ void ADODActor::Tick(float DeltaTime)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(ADODActor::Tick);
	Super::Tick(DeltaTime);
	UpdateMesh(DeltaTime);
}
