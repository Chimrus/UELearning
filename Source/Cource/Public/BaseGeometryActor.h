// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor, Color, FString, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Static
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "Movement")
	EMovementType MoveType = EMovementType::Static;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Amplitude = 50.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Frequency = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	float TimerRate = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	bool IsLoopTimer = true;
	
	UPROPERTY(VisibleAnywhere, Category = "Design")
	int32 TimerCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	int32 TimerMaxCount = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FLinearColor Color = FLinearColor::Black;
};

UCLASS()
class COURCE_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	void SetGeometryData (const FGeometryData& Data) {GeometryData = Data;}

	UFUNCTION(BlueprintCallable)
	FGeometryData GetGeometryData() const {return GeometryData;}

	UPROPERTY(BlueprintAssignable)
	FOnColorChanged OnColorChanged;
	
	FOnTimerFinished OnTimerFinished;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Data")
	FGeometryData GeometryData;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 WeaponNum = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 KillsNum = 10;

	UPROPERTY(EditInstanceOnly, Category = "Health")
	float Health = 99.99f;

	UPROPERTY(EditAnywhere, Category = "Health")
	bool bIsDead = false;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool bHasWeapon = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

private:

	FTimerHandle ColorTimer;
	void PrintStringTypes();
	void PrintTransform();
	void PrintTypes();
	void MovementHandler();
	void SetColor(const FLinearColor Color);
	void OnTimerFired();
	FVector InitialLocation;

};
