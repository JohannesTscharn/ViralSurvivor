// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" 	
#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/UObjectGlobals.h"

#include "ParticleTrigger.h" // Not in alphabetical order so I can see more easily which are my own .h)
#include "Particle.generated.h"



UCLASS()
class VIRALSURVIVOR_API AParticle : public AActor
{


	GENERATED_BODY()
	
public:	

	AParticle ();
	virtual void Tick(float DeltaTime) override;

/// JT
/// VARIABLES
///----------------------------------------------------------------------------------------------------------------------------

	// Persistent individual universal Particle Modifier 
	UPROPERTY()
	float IndRndModi;

	// Type Specifier
	UPROPERTY()
	bool CorrectType = false;
	UPROPERTY()
	bool Mismatch = false;
	UPROPERTY()
	bool LockedToVirus = false;


	// ACTIVATION
	///----------------------------------------------------------------------------------------------------------------------------
	// Activate Bool
	UPROPERTY(EditAnywhere)
	bool Activated = false;

	// Distance to Target in which Particles will be Triggered
	UPROPERTY(EditAnywhere)
	float RndActivationRadius = 2500.f;
	///----------------------------------------------------------------------------------------------------------------------------



	// TIMERS / DELAYS
	///----------------------------------------------------------------------------------------------------------------------------
	UPROPERTY()
	float FramesAlive = 0;
	
	// TimerHandles
	FTimerHandle StateTimerHandle;
	FTimerHandle SizeTimerHandle;

	int TickCounter = 0;
	int TickCounterB = 0;
	float TickCounterC = 0;
	float TickCounterD = 0;

	// Delay Time for Particle State Switch
	UPROPERTY(EditAnywhere)
	float StateSwitchDelay = 0.25f;
	///----------------------------------------------------------------------------------------------------------------------------


	// TRIGGER 
	///----------------------------------------------------------------------------------------------------------------------------
	UPROPERTY(EditAnywhere)
	AParticleTrigger* Trigger;
	// Gets the Triggers State - left Editable for Testing Purposes (will be overwritten anyway)
	UPROPERTY(EditAnywhere)
	bool TriggerActivated;
	bool TriggerWasActive;
	///----------------------------------------------------------------------------------------------------------------------------


	// Position Vectors
	FVector ParticlePosition;
	
	FVector TargetPos;
	FVector PreviousTarget;
	FVector TargetDirection;
	FVector TriggerPos; 
	FVector StartPos;
	float DistToTar;
	float TotalTarDist;

	// Rnd Position - Rnd Movement 
	FVector RndPos {0, 0, 0};
	FVector RndDir {0, 0, 0};
	FVector DirToRndTar {0, 0, 0};

	// Rnd Scale
	float RndScale;
	float MinRndScale; 
	float MaxRndScale;
	
	// - IMPORT FROM TRIGGER - Specifies the Maximum Range the Particle can Diverge from its original Position
	float maxRndMovementDist;


	// - IMPORT FROM TRIGGER - ATTRACTION FORCE
	float AttractionForce;
	// Can be Dynamically Altered to change AttractionForce without changing the base (user defined) Value for it
	float AttractionForceMult = 1.f;

	// - IMPORT FROM TRIGGER - Range in which ForceMultiplier will be effective (used to keep particles "sticky" during fast movements of the trigger)
	float AttractionRange;
	///----------------------------------------------------------------------------------------------------------------------------


///----------------------------------------------------------------------------------------------------------------------------



/// COMPONENTS / PROPERTIES
///----------------------------------------------------------------------------------------------------------------------------

	// Mesh
	UPROPERTY()
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	// Material
	UPROPERTY(EditAnywhere)
	class UMaterial* MaterialA;
	UPROPERTY(EditAnywhere)
	class UMaterial* MaterialB;
	UPROPERTY(EditAnywhere)
	class UMaterial* MaterialC;

///----------------------------------------------------------------------------------------------------------------------------



/// FUNCTIONS
/// See .cpp for further Description
///----------------------------------------------------------------------------------------------------------------------------

	// Activate / Deactivate Particle State
	UFUNCTION()
	void SwitchParticleState();

	UFUNCTION()
	void ParticleStateOff();
	UFUNCTION()
	void ParticleStateOn();
	
	UFUNCTION()
	void RndChangeState(float percent, int mode);

	// Activate / Deactivate Particle State
	UFUNCTION()
	float RandRangeF(float min, float max);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};






