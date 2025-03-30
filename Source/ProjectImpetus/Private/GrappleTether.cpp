// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleTether.h"
#include "CustomPaperCharacter.h"

// Sets default values for this component's properties
UGrappleTether::UGrappleTether()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrappleTether::MyPendulumTether(float deltaTime)
{
	SolveMyPendulumTether(deltaTime);
}

void UGrappleTether::PrepareMyPendulumTether(FVector playerPos, float tetherLength)
{
	if (AActor* Owner = GetOwner()) // Get the owning Actor
	{
		if (UPrimitiveComponent* RootPrimitive = Cast<UPrimitiveComponent>(Owner->GetRootComponent()))
		{
			float Mass = RootPrimitive->GetMass();
			UE_LOG(LogTemp, Log, TEXT("Pawn's Mass: %f"), Mass);

			uPendulumSystem->Init(
				FVector2D(playerPos.X, -playerPos.Y),
				FVector2D(PendulumPivotPoint.X, -PendulumPivotPoint.Y),
				tetherLength, Mass
			);
		}
		else
		{
			uPendulumSystem->Init(
				FVector2D(playerPos.X, -playerPos.Y),
				FVector2D(PendulumPivotPoint.X, -PendulumPivotPoint.Y),
				tetherLength
			);
		}
	}
}

void UGrappleTether::SolveMyPendulumTether(float deltaTime)
{
	if (!uPendulumSystem->GetIsActive()) { return; } // cancel any pendulum activity if not active

	if (input != 0.f)
	{
		uPendulumSystem->SetMotorSpeed(input * uPendulumSystem->GetMotorSpeedFactor());
	}
	else {
		uPendulumSystem->SetMotorSpeed(0.f);
	}
	uPendulumSystem->Update(deltaTime);

	AActor* player = GetOwner();
	FVector pos = uPendulumSystem->GetPendulumBobPosition3D();
	player->SetActorLocation(pos);
	if (UPrimitiveComponent* PlayerComp = Cast<UPrimitiveComponent>(player->GetRootComponent()))
	{
		FVector NewVelocity(uPendulumSystem->GetPlayerBob().velocity.X, 
			-uPendulumSystem->GetPlayerBob().velocity.Y, 0.f);
		PlayerComp->SetPhysicsLinearVelocity(NewVelocity);
	}

	// Detect hit on bob 
	if (ACustomPaperCharacter* paper = Cast<ACustomPaperCharacter>(player))
	{
		if (paper->HasCollided && uPendulumSystem->IsHitAllowed())
		{
			uPendulumSystem->Bounce(paper->HitDirection);
		}
		paper->HasCollided = false;
	}

	input = 0.f;
}

void UGrappleTether::PendulumPlayerInput(float axisValue)
{
	input = axisValue;
}

// Called when the game starts
void UGrappleTether::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	//uPendulumSystem = NewObject<UPendulumSystem>(this);
	uPendulumSystem = NewObject<UPendulumSystem>(this, PendulumSystemClass);
	if (uPendulumSystem)
	{
		UE_LOG(LogTemp, Log, TEXT("uPend built"));
	}
}

// Called every frame
void UGrappleTether::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
