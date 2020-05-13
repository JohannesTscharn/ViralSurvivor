// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleTrigger.h"

// JT
// -- CONSTRUCTOR --
//-------------------------------------------------------------------------------------------------------------------------
AParticleTrigger::AParticleTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootComponent = Root;
}
//-------------------------------------------------------------------------------------------------------------------------


// Called when the game starts or when spawned
void AParticleTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParticleTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called every frame
bool AParticleTrigger::IsActivated()
{
	return Activated;
}

// Called every frame
void AParticleTrigger::ActivateTrigger()
{
	Activated = true;
}
// Called every frame
void AParticleTrigger::DeActivateTrigger()
{
	Activated = false;
}
