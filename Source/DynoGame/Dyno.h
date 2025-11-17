#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Dyno.generated.h"

UENUM()
enum class  EDynoState : uint8
{
	AS_IDLE,
	AS_DUCK,
	AS_JUMP,
	AS_EMPTY,
	AS_DEAD
};

UCLASS()
class DYNOGAME_API ADyno : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADyno();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		
	void KillPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	// Declaration for the sprite
	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperFlipbookComponent* MySprite;

	// Create a capsule component
	UPROPERTY(VisibleAnywhere, Category = "Collider")
	class UCapsuleComponent* MyBodyCollider;

	// Functions for collision withe enemy and floor
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Animation flipbooks
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_Idle;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_Duck;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_Dead;

	UPROPERTY(VisibleAnywhere, Category = "Animations")
	EDynoState CurrentAnimationState;

	UPROPERTY(VisibleAnywhere, Category = "Animations")
	EDynoState OldAnimationState;

	//functions need for ducking
	void StartDucking();
	void StopDucking();
		
	void UpdateAnimation();

	// functions and variables need for jumping
	UPROPERTY(EditAnywhere, Category = "Player Properties")
	float JumpForce = 1000.0f; // can change the value in Unreal.
	void Jump();
	bool bIsJumping; //boolean that is helping to use the jump function

	float ElapsedTime;
	bool bIsClockRunning;
	
	//sounds to used and import them in unreal
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundBase* JumpSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundBase* DeadSound;
};

