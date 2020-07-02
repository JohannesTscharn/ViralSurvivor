// Fill out your copyright notice in the Description page of Project Settings.


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParticleTrigger.generated.h"

UCLASS()
class VIRALSURVIVOR_API AParticleTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParticleTrigger();
	virtual void Tick(float DeltaTime) override;



/// JT
///----------------------------------------------------------------------------------------------------------------------------


/// PROPERTIES
///----------------------------------------------------------------------------------------------------------------------------
	// Mesh
	UPROPERTY()
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	// Collider
	UPROPERTY(EditAnywhere)
	class USphereComponent* ColliderSphere;



	// Activate Bool
	UPROPERTY(EditAnywhere)
	bool Activated = true; 

	bool IsActivated();
	
///----------------------------------------------------------------------------------------------------------------------------


/// PARTICLE PROPERTIES
///----------------------------------------------------------------------------------------------------------------------------

	// ATTRACTION FORCE
	UPROPERTY(EditAnywhere)
	float TAttractionForce = 1.f;

	// Range in which ForceMultiplier will be effective (used to keep particles "sticky" during fast movements of the trigger)
	UPROPERTY(EditAnywhere)
	float TAttractionRange = 50.f;

	// Specifies the Maximum Range the Particle can Diverge from its original Position
	UPROPERTY(EditAnywhere)
	float TmaxRndMovementDist = 2.5f;

	// Rnd Scale Range
	UPROPERTY(EditAnywhere)
	float TMinRndScale = 0.5f; 
	UPROPERTY(EditAnywhere)
	float TMaxRndScale = 1.5f;

///----------------------------------------------------------------------------------------------------------------------------


/// ACTIVATE TRIGGER VIA INPUT 
/// Function is called by a grabable Actor BP via MotionController Input
///----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void ActivateTrigger();
	UFUNCTION(BlueprintCallable)
	void DeActivateTrigger();
///----------------------------------------------------------------------------------------------------------------------------

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
