// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleTether.h"

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

void UGrappleTether::PrepareMyPendulumTether(FVector2D playerPos)
{
	this->controller = GetWorld()->GetFirstPlayerController();
	//UE_LOG(LogTemp, Warning, TEXT("Actor Position: X=%f, Y=%f"), playerPos.X, playerPos.Y);
	pendulum = PendulumSystem(FVector2D(PendulumPivotPoint.X, -PendulumPivotPoint.Y),
		playerPos, 1.0f, 125.0f, 0.1f);
}

void UGrappleTether::StartMyPendulumTether(FVector2D anchorPos, FVector2D playerPos)
{
}

void UGrappleTether::SolveMyPendulumTether(float deltaTime)
{
	if (controller->IsInputKeyDown(EKeys::A))
	{
		pendulum.SetMotorSpeed(-65.0f);
		UE_LOG(LogTemp, Warning, TEXT("A key is being held down!"));
	}
	else if (controller->IsInputKeyDown(EKeys::D))
	{
		pendulum.SetMotorSpeed(65.0f);
		UE_LOG(LogTemp, Warning, TEXT("D key is being held down!"));
	}
	else {
		pendulum.SetMotorSpeed(0.f);
	}

	/*UE_LOG(LogTemp, Warning, TEXT("In Update -- Player Bob Position: X=%f, Y=%f"), 
		pendulum.playerBob.position.X, pendulum.playerBob.position.Y);*/
	pendulum.Update(deltaTime);

	// rendering
	DrawDebugLine(
		GetWorld(),
		FVector(pendulum.anchor.X, -pendulum.anchor.Y, 0.f),
		FVector(pendulum.playerBob.position.X, -pendulum.playerBob.position.Y, 0.f),
		FColor::Emerald,
		false,
		-1.0f,
		0,
		1.0f
	);
	DrawDebugCircle(
		GetWorld(),
		FVector(pendulum.playerBob.position.X, -pendulum.playerBob.position.Y, 0.f),
		16.0f,
		32,
		FColor::Emerald,
		false,
		1.0f,
		0,
		1.0f,
		FVector(1, 0, 0),
		FVector(0, 1, 0),
		false
	);
}

// Called when the game starts
void UGrappleTether::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UGrappleTether::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

