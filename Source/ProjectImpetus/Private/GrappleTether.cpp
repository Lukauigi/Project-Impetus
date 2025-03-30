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
	/*pendulum = PendulumSystemOld(
		FVector2D(PendulumPivotPoint.X, -PendulumPivotPoint.Y),
		FVector2D(playerPos.X, -playerPos.Y),
		1.0f,
		tetherLength,
		0.02f
	);*/

	UE_LOG(LogTemp, Log, TEXT("Init Call"));
	uPendulumSystem->Init(
		FVector2D(playerPos.X, -playerPos.Y),
		FVector2D(PendulumPivotPoint.X, -PendulumPivotPoint.Y),
		tetherLength
	);

}

void UGrappleTether::SolveMyPendulumTether(float deltaTime)
{
	/*if (input != 0.f)
	{
		pendulum.SetMotorSpeed(input * pendulum.motorSpeedFactor);
	}
	else {
		pendulum.SetMotorSpeed(0.f);
	}*/

	if (input != 0.f)
	{
		uPendulumSystem->SetMotorSpeed(input * pendulum.motorSpeedFactor);
	}
	else {
		uPendulumSystem->SetMotorSpeed(0.f);
	}

	UE_LOG(LogTemp, Log, TEXT("deltaTime: %f"), deltaTime);
	/*UE_LOG(LogTemp, Log, TEXT("Input: %f"), input);
	UE_LOG(LogTemp, Log, TEXT("Motor Speed: %f"), pendulum.motorSpeed);*/
	//pendulum.Update(deltaTime);
	uPendulumSystem->Update(deltaTime);

	AActor* player = GetOwner();
	// Update Player transform & velocity
	//FVector pos = pendulum.GetPendulumBobPosition3D();
	FVector pos = uPendulumSystem->GetPendulumBobPosition3D();
	player->SetActorLocation(pos);
	if (UPrimitiveComponent* PlayerComp = Cast<UPrimitiveComponent>(player->GetRootComponent()))
	{
		//FVector NewVelocity(pendulum.playerBob.velocity.X, -pendulum.playerBob.velocity.Y, 0.f);
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
			uPendulumSystem->TimeSincePendulumBounce = 0.0f;
		}

		//if (paper->HasCollided && TimeSincePendulumBounce <= 0.f)
		//{
		//	// Apply force from bouncing on wall
		//	pendulum.playerBob.velocity += FVector2D(paper->HitDirection * BounceStrength);
		//	pendulum.playerBob.angularVelocity *= -0.8f;  // Reverse direction and reduce speed slightly for realism

		//	// reset vars
		//	TimeSincePendulumBounce = PendulumBounceCooldown;
		//}
		paper->HasCollided = false;
	}

	//TimeSincePendulumBounce -= deltaTime;
	uPendulumSystem->IterateTimeSinceBounce(deltaTime);
	//uPendulumSystem->TimeSincePendulumBounce -= deltaTime;
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
