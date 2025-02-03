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

void UGrappleTether::PrepareMyPendulumTether(FVector2D playerPos)
{
	this->controller = GetWorld()->GetFirstPlayerController();
	//UE_LOG(LogTemp, Warning, TEXT("Actor Position: X=%f, Y=%f"), playerPos.X, playerPos.Y);
	pendulum = PendulumSystem(FVector2D(PendulumPivotPoint.X, -PendulumPivotPoint.Y),
		playerPos, 1.0f, 125.0f, 0.02f);
}

void UGrappleTether::StartMyPendulumTether(FVector2D anchorPos, FVector2D playerPos)
{
}

void UGrappleTether::SolveMyPendulumTether(float deltaTime)
{
	float inputStrength = 0.f;
	bool isInputDetected = false;
	if (controller->IsInputKeyDown(EKeys::A))
	{
		pendulum.SetMotorSpeed(-75.0f);
		UE_LOG(LogTemp, Warning, TEXT("A key is being held down!"));
		inputStrength = -40.0f;
		isInputDetected = true;
	}
	else if (controller->IsInputKeyDown(EKeys::D))
	{
		pendulum.SetMotorSpeed(75.0f);
		UE_LOG(LogTemp, Warning, TEXT("D key is being held down!"));
		inputStrength = 40.0f;
		isInputDetected = true;
	}
	else if (controller->IsInputKeyDown(EKeys::S))
	{
		pendulum.SlowMotorSpeed();
	}
	else {
		pendulum.SetMotorSpeed(0.f);
	}

	/*UE_LOG(LogTemp, Warning, TEXT("In Update -- Player Bob Position: X=%f, Y=%f"), 
		pendulum.playerBob.position.X, pendulum.playerBob.position.Y);*/
	pendulum.Update(deltaTime);
	AActor* player = GetOwner();
	
	if (ACustomPaperCharacter* paper = Cast<ACustomPaperCharacter>(player))
	{
		UE_LOG(LogTemp, Log, TEXT("Casted Paper Char"));
		if (paper->HasCollided)
		{
			UE_LOG(LogTemp, Log, TEXT("Has Collided"));
			UE_LOG(LogTemp, Log, TEXT("(Before) Angular Velocity=%f"), pendulum.playerBob.angularVelocity);
			// Reverse angular velocity to make it bounce back
			pendulum.playerBob.angularVelocity *= -0.8f;  // Reverse direction and reduce speed slightly for realism
			UE_LOG(LogTemp, Log, TEXT("(After) Angular Velocity=%f"), pendulum.playerBob.angularVelocity);
			// Optionally reset the collision flag after handling
			paper->HasCollided = false;
			
		}
	}


	// Update Player transform & velocity
	FVector pos = pendulum.GetPendulumBobPosition3D();
	player->SetActorLocation(pos);
	if (UPrimitiveComponent* PlayerComp = Cast<UPrimitiveComponent>(player->GetRootComponent()))
	{
		FVector NewVelocity(pendulum.playerBob.velocity.X, -pendulum.playerBob.velocity.Y, 0.f);
		PlayerComp->SetPhysicsLinearVelocity(NewVelocity);
	}

	// debug rendering
	DrawDebugLine(
		GetWorld(),
		pendulum.GetPendulumAnchorPosition3D(),
		pendulum.GetPendulumBobPosition3D(),
		FColor::Emerald,
		false,
		-1.0f,
		0,
		1.0f
	);
	DrawDebugCircle(
		GetWorld(),
		pendulum.GetPendulumBobPosition3D(),
		16.0f,
		32,
		FColor::Emerald,
		false,
		0.5f,
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

