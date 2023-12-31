// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPawn.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPawn, All,All)

// Sets default values
ASandboxPawn::ASandboxPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene component");
	SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void ASandboxPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASandboxPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!VelocityVector.IsZero())
	{
		const FVector NewLocation = GetActorLocation() + Velocity * DeltaTime * VelocityVector;
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawn::MoveRight);
}

void ASandboxPawn::MoveForward(float Amount)
{
	UE_LOG(LogSandboxPawn, Warning, TEXT("Move forvard amount:%f"), Amount);
	VelocityVector.Y = Amount;
}

void ASandboxPawn::MoveRight(float Amount)
{
	UE_LOG(LogSandboxPawn, Warning, TEXT("Move right amount:%f"), Amount);
	VelocityVector.X = Amount;
}

