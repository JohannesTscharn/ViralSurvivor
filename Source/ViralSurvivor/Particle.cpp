
#include "Math/UnrealMathUtility.h"
#include "Particle.h"

//-------------------------------------------------------------------------------------------------------------------------
// -- CONSTRUCTOR --
//-------------------------------------------------------------------------------------------------------------------------
AParticle::AParticle()
{
	PrimaryActorTick.bCanEverTick = true;

	// Root Component
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootComponent = Root;
	
	// Mesh Component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ParticleMesh"));
	Mesh->AttachTo(Root);
	// Select the Preset-Sphere
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	// After NullPointer Save -> Assign Mesh
	if (MeshAsset.Object != nullptr)
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
	}


	// Material
	MaterialA = CreateDefaultSubobject<UMaterial>(TEXT("MaterialA"));
	MaterialB = CreateDefaultSubobject<UMaterial>(TEXT("Material"));
	MaterialC = CreateDefaultSubobject<UMaterial>(TEXT("MaterialB"));


	// Persistent individual universal Particle Modifier 
	// used for weighting multiple parameters like Attraction Force: +-50%
	// Initialized in Constructor to keep it Constant and unique to each Particle - increases randomness
	IndRndModi = FMath::RandRange(0.5f, 1.5f);



	// --------------------------------- EXPERIMENTAL / DISCARDED  ---------------------------------

} // END CONSTRUCTOR
//-------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------
// BEGIN PLAY
//-------------------------------------------------------------------------------------------------------------------------
void AParticle::BeginPlay()
{
	Super::BeginPlay();

	// Get the Particles Starting Position and Store for later use
	StartPos = GetActorLocation();
	// Initialize the Target Position to the Starting Position (Particle will not move by default)
	TargetPos = StartPos;

	// Assign Material 1 as Default Material (cannot be done in Constructor for some reason)
	if (MaterialA != nullptr && MaterialB != nullptr)
		Mesh->SetMaterial(0, MaterialA);

	// Randomize Actor Scale
	
	// Update Trigger Scale Parameter (after NullPointer Safe)
	if (Trigger != nullptr)
	{
		MinRndScale = Trigger->TMinRndScale;
		MaxRndScale = Trigger->TMaxRndScale;
	}

	float rndType = RandRangeF(0.0f, 1.0f);
	if (rndType > 0.25f)
		CorrectType = true;

	if (!CorrectType)
		RndScale = RandRangeF(MinRndScale, MaxRndScale);
	else
		RndScale = RandRangeF(MinRndScale / 2, MaxRndScale / 2);


} // END BEGIN PLAY
//-------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------
// TICK FUNCTION
//-------------------------------------------------------------------------------------------------------------------------
void AParticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get the Particles Current Position
	ParticlePosition = GetActorLocation();

	// Get Trigger State (after NullPointer Safe)
	if (Trigger != nullptr)
		TriggerActivated = Trigger->IsActivated();

	// Calculate Tirection + Distance to the TargetPosition
	TargetDirection = TargetPos - ParticlePosition;
	DistToTar = TargetDirection.Size();




//-------------------------------------------------------------------------------------------------------------------------
// MOVEMENT
//-------------------------------------------------------------------------------------------------------------------------
	

	// Update Trigger Position (after NullPointer Safe)
	if (Trigger != nullptr){
		TriggerPos = Trigger->GetActorLocation();

		// Set Particle Variables as specified by User in Trigger
		maxRndMovementDist = Trigger->TmaxRndMovementDist;

		if (!LockedToVirus)
			AttractionForce = Trigger->TAttractionForce;
		else 
			AttractionForce = 2.5f;

		AttractionRange = Trigger->TAttractionRange;


		// Calculate Distance to Trigger every Frame
		FVector TriggerDir = TriggerPos - GetActorLocation();
		float TriggerDist = TriggerDir.Size();
		if (TriggerDist <= 0)
			TriggerDist *= -1;

	//-------------------------------------------------------------------------------------------------------------------------
	// PARTICLE MOVEMENT (Update Target with Delay)
	//-------------------------------------------------------------------------------------------------------------------------


	// TICKER 1
	// Updates the Target Position every N Frames
	//------------------------------------------------------------------------------------------------------------------
	TickCounter += 1; 

	// Random Event Selector based on Ticker #1
	// Ticks every N Frames
	if (TickCounter >= RandRangeF(15, 35)){
		
		// Set TargetPosition to Initial (Start) Position by Default
		if (TriggerActivated && !Mismatch)
		{
			if (TriggerDist < AttractionRange * IndRndModi && TriggerDist > 5.0f)
			{
				RndChangeState(0.5f, 2);
				// Target is AttractionForce Position for N Cases
				TargetPos = TriggerPos;
			}
			// Ensure Target Pos is AttrSourcePos once "Grabbed"
			if (TargetPos != StartPos && TriggerDist > 75.0f)
			{
				if (TriggerDist > 75.0f)
				{
					TargetPos = TriggerPos;
				}
				if (TriggerDist <= 100.f)
				{
					// Type Check
					if (!CorrectType)
					{
						TargetPos = StartPos;
						Mismatch = true;
					}
					else
					{
						TargetPos = TriggerPos;
						LockedToVirus = true;
					}
					
				}
			}
			
			if (TargetPos == TriggerPos)
				Activated = true;

		}
		else
		{
			// Move back to StartPos
			TargetPos = StartPos;
		}

		// TODO SET TotalTarDist to ZERO!!! 
		TickCounter = 0;
	} // TICKER 1 END

	if (TargetPos == StartPos)
	{
		TickCounterC += 1;
		if (TickCounterC > RandRangeF(5.f, 50.f))
		{
			RndChangeState(.5f, 3);
			TickCounterC = 0;
		}
	}


	//------------------------------------------------------------------------------------------------------------------
	// Calculate new Particle Position - Influenced by AttractionForce & DistanceToTarget (Move faster the further away)
	FVector TDirNorm = TargetDirection.GetSafeNormal(0.001f);
	ParticlePosition += (TDirNorm * DeltaTime * (AttractionForce * AttractionForceMult) * (DistToTar * IndRndModi));
	//------------------------------------------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------------------------------------------------
		

	//-------------------------------------------------------------------------------------------------------------------------
	// PARTICLE MOVEMENT (Random Movement - Jitter)
	//-------------------------------------------------------------------------------------------------------------------------

		// TICKER 2
		// Creates a Random Position every N Frames
		//------------------------------------------------------------------------------------------------------------------
		TickCounterB += 1;
			
			// Change to Influence the Particles "Snappyness" - Target is Updated more regularely
		if (TickCounterB >= RandRangeF(150, 800))
		{
			// Create Random Location (MaxRange from ParticlePos is User Defined)
			float Rng = maxRndMovementDist;
			RndDir = {RandRangeF(-Rng, Rng), RandRangeF(-Rng, Rng), RandRangeF(-Rng, Rng)};
			// Direction Vector - Normalized
			DirToRndTar = RndDir;
			RndDir = RndDir.GetSafeNormal(0.001f);
				
			// Sometimes Particles Switch State when jumping
			RndChangeState(.25f, 1);
			// Limit the amount of ON Particles further
			RndChangeState(.75f, 3);

			// Update Scale
			// float tempRnd = RandRangeF(MinRndScale, MaxRndScale);
			// FVector StateScale {tempRnd, tempRnd, tempRnd};
			// SetActorScale3D(StateScale);

			// Reset "Timer"
			TickCounterB = 0;

		} // TICKER 2 END
		//------------------------------------------------------------------------------------------------------------------		

		// Update distance to RndLoc every frame
		float distToRndLoc = DirToRndTar.Size();
		// Calculate new Particle Position - weighted by the universal individual particle modifier
		ParticlePosition += RndDir;

	//-------------------------------------------------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------------------------------------------------
	// PARTICLE MOVEMENT (passive Trigger Attraction)
	//-------------------------------------------------------------------------------------------------------------------------

			// Activate Particle when in close proximity to Trigger (User Defined) - with probability
			if (TriggerDist <= ((AttractionRange / 2) * IndRndModi))
			{
				Activated = true;
			}
		} 

	//-------------------------------------------------------------------------------------------------------------------------


	// Finally Transform Actor (Particle) Position 
	SetActorLocation(ParticlePosition);


//-------------------------------------------------------------------------------------------------------------------------
// PARTICLE STATE EFFECTS
//-------------------------------------------------------------------------------------------------------------------------

// Update Material 
//-------------------------------------------------------------------------------------------------------------------------
	if (!CorrectType)
	{
			Mesh->SetMaterial(0, MaterialC);
	}
	if (Activated)
	{
		// Update Material 
		if (MaterialA != nullptr && MaterialB != nullptr && MaterialC != nullptr)
		{
			Mesh->SetMaterial(0, MaterialB);

		}


			// Set Size to Nomal Value
			FVector StartSize {(MinRndScale / 3), (MinRndScale / 3), (MinRndScale / 3)};
			SetActorScale3D(StartSize);

	}
	else
	{
		// Update Material 
		if (MaterialA != nullptr && MaterialB != nullptr && MaterialC != nullptr)
		{
			if (CorrectType)
				Mesh->SetMaterial(0, MaterialA);
			else 
				Mesh->SetMaterial(0, MaterialC);
		}
		FVector DeactivateScale {MinRndScale / 2, MinRndScale / 2, MinRndScale / 2};
		SetActorScale3D(DeactivateScale);

	}
//-------------------------------------------------------------------------------------------------------------------------


} // END TICK
//-------------------------------------------------------------------------------------------------------------------------










//-------------------------------------------------------------------------------------------------------------------------
// CUSTOM FUNCTIONS 
//-------------------------------------------------------------------------------------------------------------------------


// Switch Particle State
void AParticle::SwitchParticleState()
{
		if (!Activated)
			Activated = true;
		else
			Activated = false;
}

void AParticle::ParticleStateOn()
{
		Activated = true;
}

void AParticle::ParticleStateOff()
{
		Activated = false;
}

// Switch Particle State with a user defined probability
// Modes: (1 is switch, 2 is turn on, 3 is turn off)
void AParticle::RndChangeState(float probability, int mode)
{
	float TempRndNbr = FMath::RandRange(0.f, 1.f);
	if (probability >= TempRndNbr)
	{
		if (mode == 1)
			SwitchParticleState();
		else if (mode == 2)
			ParticleStateOn();
		else if (mode == 3)
			ParticleStateOff();
	}
}

// Simple helper function - Shorter Code (Could be left out, but I like it without the FMath::(...) every time)
float AParticle::RandRangeF(float min, float max)
{
	float RndRange = FMath::RandRange(min, max);
	return RndRange;
}

//-------------------------------------------------------------------------------------------------------------------------
