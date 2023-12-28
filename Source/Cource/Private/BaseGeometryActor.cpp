// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	SetColor(GeometryData.Color);
	InitialLocation = GetActorLocation();
	GetWorldTimerManager().SetTimer(ColorTimer, this, &ABaseGeometryActor::OnTimerFired, GeometryData.TimerRate, true);


	//PrintTypes();
}

void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor %s was destroyed"), *GetName());
	Super::EndPlay(EndPlayReason);
}

void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovementHandler();
}

void ABaseGeometryActor::PrintStringTypes()
{
	FString Name = "John Connor";
	UE_LOG(LogBaseGeometry, Display, TEXT("Name: %s"), *Name);

	FString WeaponsNumStr = "Weapons num: " + FString::FromInt(WeaponNum);
	FString HealthStr = "Health: " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "Is dead: " + FString(bIsDead ? "true" : "false");
	//FString StatsStr = WeaponsNumStr + HealthStr + IsDeadStr;
	FString StatsString = FString::Printf(
		TEXT(" \n == All stats == \n \t %s \n \t %s \n \t %s"), *WeaponsNumStr, *HealthStr, *IsDeadStr);
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *StatsString);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Green, Name);
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, StatsString, true, FVector2d(2.f));
	}
}

void ABaseGeometryActor::PrintTransform()
{
	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Transform %s"), *Transform.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Location %s"), *Location.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Rotation %s"), *Rotation.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Scale %s"), *Scale.ToString());
	UE_LOG(LogBaseGeometry, Error, TEXT("Human Transform %s"), *Transform.ToHumanReadableString());
}

void ABaseGeometryActor::PrintTypes()
{
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Weapon num: %d, kills num %i"), WeaponNum, KillsNum);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Health: %f"), Health);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Is dead: %d"), bIsDead);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Has weapon: %d"), static_cast<int>(bHasWeapon));
}

void ABaseGeometryActor::MovementHandler()
{
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
		{
			if (GetWorld())
			{
				float time = GetWorld()->GetTimeSeconds();
				FVector CurrentLocation = GetActorLocation();
				CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(
					GeometryData.Frequency * time);
				SetActorLocation(CurrentLocation);
			}
		}
		break;
	case EMovementType::Static: break;
	default: break;
	}
}

void ABaseGeometryActor::SetColor(const FLinearColor Color)
{
	if (BaseMesh)
	{
		UMaterialInstanceDynamic* DynMat = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
		if (DynMat)
		{
			DynMat->SetVectorParameterValue("Color", Color);
		}
	}
}

void ABaseGeometryActor::OnTimerFired()
{
	if (++GeometryData.TimerCount <= GeometryData.TimerMaxCount && !GeometryData.IsLoopTimer)
	{
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
		UE_LOG(LogBaseGeometry, Display, TEXT("Timer iteration: %i \n New color is %s"), GeometryData.TimerCount,
		       *NewColor.ToString());
		SetColor(NewColor);
		OnColorChanged.Broadcast(NewColor, GetName());
		return;
	}
	if (GeometryData.IsLoopTimer)
	{
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
		UE_LOG(LogBaseGeometry, Display, TEXT("New color is %s"), *NewColor.ToString());
		SetColor(NewColor);
		OnColorChanged.Broadcast(NewColor, GetName());
		return;
	}
	GetWorldTimerManager().ClearTimer(ColorTimer);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Timer is cleared!"));
	OnTimerFinished.Broadcast(this);
}
