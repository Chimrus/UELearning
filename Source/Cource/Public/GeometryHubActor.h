// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGeometryActor.h"
#include "GameFramework/Actor.h"
#include "GeometryHubActor.generated.h"

class ABaseGeometryActor;

USTRUCT(BlueprintType)
struct FGeometryPayLoad
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;

	UPROPERTY(EditAnywhere)
	FGeometryData Data;

	UPROPERTY(EditAnywhere)
	FTransform InitialTransform;
};

UCLASS()
class COURCE_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGeometryHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;

	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayLoad> GeometryPayLoad;

private:

	UFUNCTION()
	void FOnColorChanged( const FLinearColor Color, FString Name);

	void FOnTimerFinished (AActor* Actor);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
