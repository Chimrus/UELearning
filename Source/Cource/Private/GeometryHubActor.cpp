// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"

#include <string>

#include "BaseGeometryActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All)


// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();
	if (UWorld* World = GetWorld())
	{
		for (const FGeometryPayLoad Element : GeometryPayLoad)
		{
			ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(
				Element.GeometryClass, Element.InitialTransform);
			if (Geometry)
			{
				Geometry->SetGeometryData(Element.Data);
				Geometry->OnColorChanged.AddDynamic(this, &AGeometryHubActor::FOnColorChanged);
				Geometry->OnTimerFinished.AddUObject(this, &AGeometryHubActor::FOnTimerFinished);
				Geometry->FinishSpawning(Element.InitialTransform);
			}
		}
	}
}

void AGeometryHubActor::FOnColorChanged(const FLinearColor Color, FString Name)
{
	UE_LOG(LogGeometryHub, Warning, TEXT("Actor name : %s Color %s"), *Name, *Color.ToString());
}

void AGeometryHubActor::FOnTimerFinished(AActor* Actor)
{
	if (!Actor) return;
	UE_LOG(LogGeometryHub, Warning, TEXT("Timer finished : %s"), *Actor->GetName());

	ABaseGeometryActor* Geometry = Cast<ABaseGeometryActor>(Actor);
	if (!Geometry) return;
	UE_LOG(LogGeometryHub, Warning, TEXT("Cast success, amplitude : %f"), Geometry->GetGeometryData().Amplitude);
	Geometry->Destroy();
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
