// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class DYNOGAME_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Sprite component to display the enemy
	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperFlipbookComponent* MySprite;

	//Box component for the collision
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* BoxComp;

	// Base speed of the enemy
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MoveSpeed;
};
