// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DynoGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DYNOGAME_API ADynoGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    ADynoGameGameModeBase();
        
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to stop the game and handle end game logic
    void EndGame();

    UFUNCTION(BlueprintCallable, Category = "Game")
    float GetElapsedTime() const;

    // Function to reset the elapsed time
    UFUNCTION(BlueprintCallable, Category = "Game")
    void ResetElapsedTime();
    
    float ElapsedTime;  

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    // Boolean to control whether the clock is running
    bool bIsClockRunning;
    
   
};