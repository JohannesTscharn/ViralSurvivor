// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Virus_MembraneStage.generated.h"

UCLASS()
class VIRALSURVIVOR_API AVirus_MembraneStage : public AActor
{
	GENERATED_BODY()
	
public:	
	AVirus_MembraneStage();
	virtual void Tick(float DeltaTime) override;

///----------------------------------------------------------------------------------------------------------------------------
/// PROPERTIES
///----------------------------------------------------------------------------------------------------------------------------

	// Mesh
	UPROPERTY()
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;



	UPROPERTY(EditAnywhere)
	AActor* Protein;
///----------------------------------------------------------------------------------------------------------------------------



///----------------------------------------------------------------------------------------------------------------------------
/// VARIABLES
///----------------------------------------------------------------------------------------------------------------------------

	UPROPERTY()
	FVector VirusPos;
	UPROPERTY()
	float DistToProtein = 0.f;
	UPROPERTY(EditAnywhere)
	float AttractionRange;


	UPROPERTY()
	FVector ProteinPos;



///----------------------------------------------------------------------------------------------------------------------------




protected:
	virtual void BeginPlay() override;

};
