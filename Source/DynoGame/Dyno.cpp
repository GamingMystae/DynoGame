// Fill out your copyright notice in the Description page of Project Settings.


#include "Dyno.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Enemy.h"
#include <Kismet/GameplayStatics.h>
#include "DynoGameGameModeBase.h"


// Sets default values
ADyno::ADyno()
{
    PrimaryActorTick.bCanEverTick = true;

    //creatung the collider and set it too the root
    MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    MyBodyCollider->InitCapsuleSize(42.f, 96.0f);
    SetRootComponent(MyBodyCollider);


    // creating the sprite and attache it with MyBodyColider
    MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("SpriteComponent"));
    MySprite->SetupAttachment(RootComponent);
       
    //set the start animation
    CurrentAnimationState = EDynoState::AS_IDLE;
    OldAnimationState = EDynoState::AS_EMPTY;

    //seting the variable false
    bIsJumping = false;
}

// Called when the game starts or when spawned
void ADyno::BeginPlay()
{
    Super::BeginPlay();
    
    //trigger the collision with floor
    MyBodyCollider->OnComponentHit.AddDynamic(this, &ADyno::OnCollision);

    //trigger the collision with enemy
    MyBodyCollider->OnComponentBeginOverlap.AddDynamic(this, &ADyno::OnOverlapBegin);
    
    UpdateAnimation();
}

// Called every frame
void ADyno::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bIsJumping && CurrentAnimationState != EDynoState::AS_DUCK)
    {
        CurrentAnimationState = EDynoState::AS_IDLE;
    }

    UpdateAnimation();
}

// Called to bind functionality to input
void ADyno::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // binding the keys
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADyno::Jump);
    PlayerInputComponent->BindAction("Duck", IE_Pressed, this, &ADyno::StartDucking);
    PlayerInputComponent->BindAction("Duck", IE_Released, this, &ADyno::StopDucking);
}

void ADyno::StartDucking()
{
    if (CurrentAnimationState == EDynoState::AS_IDLE || CurrentAnimationState == EDynoState::AS_JUMP)
    {
        CurrentAnimationState = EDynoState::AS_DUCK;
        MyBodyCollider->SetCapsuleSize(42.f, 48.0f);  //change the size of the capsule and avoid with bat collision
        UpdateAnimation();
    }
}

void ADyno::StopDucking()
{
    if (CurrentAnimationState == EDynoState::AS_DUCK)
    {
        CurrentAnimationState = EDynoState::AS_IDLE;
        MyBodyCollider->SetCapsuleSize(42.f, 96.0f);  // Reset size for idle
        UpdateAnimation();
    }
}



void ADyno::Jump()
{
    if (!bIsJumping)
    {
        
        if (CurrentAnimationState == EDynoState::AS_DUCK)
        {
            // resize the size if the dyno was in duck animation
           MyBodyCollider->SetCapsuleSize(42.f, 96.0f);
        }

        if (JumpForce > 0)
        {
            MyBodyCollider->AddImpulse(FVector(0, 0, 1) * JumpForce * MyBodyCollider->GetMass()); //jumping using physics (AddImpulse and Mass)
            
            bIsJumping = true; // setting the boolean to true so dyno cant jump while is on the air
            
            UGameplayStatics::PlaySound2D(GetWorld(), JumpSound); // calling the jump sound
            CurrentAnimationState = EDynoState::AS_JUMP; //change the animation
            UpdateAnimation();
                      
        }
    }
}

// Overlap event with enemies and destroy the enemy
void ADyno::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && OtherComp)
    {
        if (AEnemy* Enemy = Cast<AEnemy>(OtherActor))
        {
            KillPlayer(); // call the killerplayer function
        }
    }
}

void ADyno::KillPlayer()
{
    CurrentAnimationState = EDynoState::AS_DEAD;
    UpdateAnimation();

    UGameplayStatics::PlaySound2D(GetWorld(), DeadSound);

    DisableInput(nullptr);

    // Stop the game in the game mode
    ADynoGameGameModeBase* GameMode = Cast<ADynoGameGameModeBase>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->EndGame(); //from game mode using the EndGame function
    }
}

void ADyno::UpdateAnimation()
{
     /// the way for updating the animation
    if (CurrentAnimationState != OldAnimationState)
    {
        switch (CurrentAnimationState)
        {
        case EDynoState::AS_IDLE:
           
            MySprite->SetFlipbook(Flipbook_Idle);
           
            break;
        case EDynoState::AS_DUCK:
            
            MySprite->SetFlipbook(Flipbook_Duck);
            
            break;
        case EDynoState::AS_JUMP:
            
            MySprite->SetFlipbook(Flipbook_Jump);
           
            break;
        case EDynoState::AS_DEAD:
            
            MySprite->SetFlipbook(Flipbook_Dead);
            
            break;
        default:
            break;
        }

        OldAnimationState = CurrentAnimationState;
    }
}

// collison with the ground so the Dyno can jump again
void ADyno::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    
    if (OtherActor->ActorHasTag("Land"))  //using the tag to reset the jump boolean and cgange the animation
    {
        bIsJumping = false; //reseting the boolean so the dyno can jump again

        if (CurrentAnimationState != EDynoState::AS_DUCK)
        {
            CurrentAnimationState = EDynoState::AS_IDLE; //changing the animation to idle
        }

        UpdateAnimation();

    }
}