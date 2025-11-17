// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Dyno.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set BoxComp as RootComponent first
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(BoxComp);

	// Attach sprite components to the root
	MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("SpriteComponent"));
	MySprite->SetupAttachment(RootComponent);
	
	//set basespeed -70 for left movement
	MoveSpeed = 100.0f;
		
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Implement movement by updating the X location each frame based on MoveSpeed
	FVector NewLocation = GetActorLocation();
	NewLocation.X -= MoveSpeed * DeltaTime;  // Increment X by MoveSpeed * DeltaTime

	// Checking boundaries on the X axis
	if (NewLocation.X < -265)
	{
		Destroy(); // Destroy the actor when it moves off-screen to the left
	}

	// Set the updated location
	SetActorLocation(NewLocation);
}

