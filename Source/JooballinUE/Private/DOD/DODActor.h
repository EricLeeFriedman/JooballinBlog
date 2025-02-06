// License Copyright (c) 2025 Eric Friedman

#pragma once

// Includes
// -------------------------------------

// Engine
#include "GameFramework/Actor.h"

// Auto-generated
#include "DODActor.generated.h"

/**
 * Actor to demonstrate tick times on a per-actor basis
 */
UCLASS(Abstract)
class ADODActor : public AActor
{
	GENERATED_BODY()

public:
	ADODActor();

	void UpdateMesh(const float DeltaTime);

	float UpdateZ = 0.0f;

	UPROPERTY(Transient)
	TObjectPtr<UMaterialInstanceDynamic> MaterialInstance;

protected:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	//~ End AActor Interface

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> Material;
};
