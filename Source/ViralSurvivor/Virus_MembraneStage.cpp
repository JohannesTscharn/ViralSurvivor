// Fill out your copyright notice in the Description page of Project Settings.


#include "Virus_MembraneStage.h"


//-------------------------------------------------------------------------------------------------------------------------
// CONSTRUCTOR
//-------------------------------------------------------------------------------------------------------------------------
AVirus_MembraneStage::AVirus_MembraneStage()
{
	PrimaryActorTick.bCanEverTick = true;


	// Root Component
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootComponent = Root;
	
	// Mesh Component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Virus Mesh"));
	Mesh->AttachTo(Root);

	if (Protein != nullptr)
	{
		ProteinPos = Protein->GetActorLocation;
	}

} // END CONSTRUCTOR
//-------------------------------------------------------------------------------------------------------------------------




//-------------------------------------------------------------------------------------------------------------------------
// BEGIN PLAY
//-------------------------------------------------------------------------------------------------------------------------
void AVirus_MembraneStage::BeginPlay()
{
	Super::BeginPlay();
	
} // END BEGIN PLAY
//-------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------
// TICK
//-------------------------------------------------------------------------------------------------------------------------
void AVirus_MembraneStage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Calculate Distance to Protein
	if (ProteinPos != nullptr)
	{
		// Calculate Distance to Trigger every Frame
		FVector ProteinDir = ProteinPos - GetActorLocation();
		DistToProtein = ProteinDir.Size();
	}

	if (DistToProtein <= AttractionRange && DistToProtein > 0.5f)
	{
		SetActorLocation(ProteinPos);
	}

} // END TICK
//-------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------
// CUSTOM FUNCTIONS 
//-------------------------------------------------------------------------------------------------------------------------

