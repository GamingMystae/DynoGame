// Copyright Epic Games, Inc. All Rights Reserved.

#include "DynoGameGameModeBase.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"


ADynoGameGameModeBase::ADynoGameGameModeBase()
{
   
    // Enable ticking for this class
    PrimaryActorTick.bCanEverTick = true;

    //set time 0
    ElapsedTime = 0.0f;
    
    //set the boolean to false
    bIsClockRunning = false;
    
   
}

void ADynoGameGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    // Start the clock when the game begins
    bIsClockRunning = true;

   
}

void ADynoGameGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update the elapsed time if the clock is running
    if (bIsClockRunning)
    {
        ElapsedTime += DeltaTime;
       
    }
}

void ADynoGameGameModeBase::EndGame()
{
    // Stop the clock
    bIsClockRunning = false;

    // opent the level gameover
    UGameplayStatics::OpenLevel(this, FName(TEXT("L_GameOver")), false);
}

float ADynoGameGameModeBase::GetElapsedTime() const
{
    return ElapsedTime;
}
void ADynoGameGameModeBase::ResetElapsedTime()
{
    ElapsedTime = 0.0f;
    bIsClockRunning = true;
}


