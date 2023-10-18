// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossSectionActor.h"

#include <string>

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
	CrossSectionSurface->OnComponentBeginOverlap.AddDynamic(this, &ACrossSectionActor::OnOverlapBegin);
	CrossSectionSurface->OnComponentEndOverlap.AddDynamic(this, &ACrossSectionActor::OnOverlapEnd);

}

void ACrossSectionActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector PointOnSurface = OtherActor->GetActorLocation() - FVector::DotProduct(Normals[0], OtherActor->GetActorLocation() - CrossSectionSurface->GetComponentLocation()) * Normals[0];
	
	OverlappedActors.insert({OtherActor, {OtherActor, OtherComp, PointOnSurface}});
}

void ACrossSectionActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappedActors.erase(OtherActor);
	
}



// Called every frame
void ACrossSectionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (auto const& pair: OverlappedActors)
	{
		// Produce ray from other to cross section surface
		// The ray should be the shortest possible from other center to the surface
		// this will produce a point on the cross section surface that then we can produce rays from surface verts and edges towards other so we get the cross section shape
		
	}
	
}

