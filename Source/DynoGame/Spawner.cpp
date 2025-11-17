// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Enemy.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SetRootComponent(SceneComponent);
	
	SpawnTimeMin = 2.0f; // Minimum Random spawn time
	SpawnTimeMax = 4.0f; // Maximum random spawn time
	WaitTimeSpawning = 1.5f; // time to wait beetween spawning

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// Start the spawning 
	SetRandomSpawnTimer();
	
}
	

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::SpawnEnemy()
{
	if (EnemyClass)
	{
		// Get the location and rotation of the spawner actor
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();

		// Spawn the enemy
		AEnemy* SpawnedEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass, SpawnLocation, SpawnRotation);

		// Set the next random spawn timer after spawning
		SetRandomSpawnTimer();
	}
	
}

void ASpawner::SetRandomSpawnTimer()
{
	// Generate a random spawn time between  min and max time
	float RandomSpawnTime = FMath::RandRange(SpawnTimeMin, SpawnTimeMax);

	// waiting between spawns
	RandomSpawnTime = FMath::Max(RandomSpawnTime, WaitTimeSpawning);

	// Set a new timer for the next spawn with the random Spawn time
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawner::SpawnEnemy, RandomSpawnTime, false);
		
}