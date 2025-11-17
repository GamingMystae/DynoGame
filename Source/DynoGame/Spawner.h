// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class DYNOGAME_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASpawner();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// The root component for positioning the spawner
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* SceneComponent;

	// The enemy class to spawn
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemy> EnemyClass;

	// Function to spawn an enemy
	void SpawnEnemy();
	// Minimum spawn interval in seconds
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float SpawnTimeMin;

	// Maximum spawn interval in seconds
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float SpawnTimeMax;

	// Timer handle for the spawning
	FTimerHandle SpawnTimerHandle;

	// Sets a new random spawn timer
	void SetRandomSpawnTimer();

	// time to wait between spawns and avoid spawnings enemies at the same time and it is imposible to avoid collision
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float WaitTimeSpawning;
};