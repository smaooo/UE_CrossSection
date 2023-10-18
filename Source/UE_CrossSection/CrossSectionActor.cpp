// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossSectionActor.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
ACrossSectionActor::ACrossSectionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CrossSectionSurface = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrossSectionSurface"));

}

void ACrossSectionActor::InitVertices()
{
	UStaticMesh* mesh = CrossSectionSurface->GetStaticMesh();
	UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(mesh, 0, 0, Vertices, Triangles, Normals, UVs, Tangents);

	
	for (FVector &vert : Vertices)
	{
		vert *= CrossSectionSurface->GetComponentScale();
		const FRotator rotation = CrossSectionSurface->GetComponentRotation();
		vert = rotation.RotateVector(vert);
		vert += CrossSectionSurface->GetComponentLocation();
	}
}


// Called when the game starts or when spawned
void ACrossSectionActor::BeginPlay()
{
	Super::BeginPlay();

	this->InitVertices();
}

// Called every frame
void ACrossSectionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

