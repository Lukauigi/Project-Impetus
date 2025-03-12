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
	pendulum = PendulumSystem(FVector2D(PendulumPivotPoint.X, -PendulumPivotPoint.Y),
		playerPos, 1.0f, 125.0f, 0.02f);
}

void UGrappleTether::SolveMyPendulumTether(float deltaTime)
{
	if (controller->IsInputKeyDown(EKeys::A))
	{
		pendulum.SetMotorSpeed(-75.0f);
	}
	else if (controller->IsInputKeyDown(EKeys::D))
	{
		pendulum.SetMotorSpeed(75.0f);
	}
	else if (controller->IsInputKeyDown(EKeys::S))
	{
		pendulum.SlowMotorSpeed();
	}
	else {
		pendulum.SetMotorSpeed(0.f);
	}

	pendulum.Update(deltaTime);
	AActor* player = GetOwner();

	// Update Player transform & velocity
	FVector pos = pendulum.GetPendulumBobPosition3D();
	player->SetActorLocation(pos);
	if (UPrimitiveComponent* PlayerComp = Cast<UPrimitiveComponent>(player->GetRootComponent()))
	{
		FVector NewVelocity(pendulum.playerBob.velocity.X, -pendulum.playerBob.velocity.Y, 0.f);
		PlayerComp->SetPhysicsLinearVelocity(NewVelocity);
	}

	// Detect hit on bob 
	if (ACustomPaperCharacter* paper = Cast<ACustomPaperCharacter>(player))
	{
		if (paper->HasCollided && TimeSincePendulumBounce <= 0.f)
		{
			// Apply force from bouncing on wall
			pendulum.playerBob.velocity += FVector2D(paper->HitDirection * BounceStrength);
			pendulum.playerBob.angularVelocity *= -0.8f;  // Reverse direction and reduce speed slightly for realism
			
			// reset vars
			TimeSincePendulumBounce = PendulumBounceCooldown;
		}
		paper->HasCollided = false;
	}

	TimeSincePendulumBounce -= deltaTime;

	/*FName FunctionName = "UpdateTetherVisuals";
	UFunction* Function = this->FindFunction(FunctionName);
	if (Function)
	{
		UE_LOG(LogTemp, Warning, TEXT("called BP func from c++ pendulum"));
		this->ProcessEvent(Function, nullptr);
	}*/

	// debug rendering
	/*DrawDebugLine(
		GetWorld(),
		pendulum.GetPendulumAnchorPosition3D(),
		pendulum.GetPendulumBobPosition3D(),
		FColor::Emerald,
		false,
		-1.0f,
		0,
		1.0f
	);*/
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

