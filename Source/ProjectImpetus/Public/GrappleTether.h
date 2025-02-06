// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrappleTether.generated.h"

// Constants
const double GRAVITY = 9.8;

struct RB2D {
	FVector2D position;
	FVector2D velocity;
	float angle;
	float angularVelocity;
	float angularAcceleration;
	float mass;
	float momentOfInertia;

	RB2D(FVector2D pos, float mass, float inertia) : position(pos), velocity(0.f, 0.f), 
		angle(0.f), angularVelocity(0.f), angularAcceleration(0.f), mass(mass), momentOfInertia(inertia) {}
	// init with starting angle
	RB2D(FVector2D pos, float mass, float inertia, float angle) : position(pos), velocity(0.f, 0.f),
		angle(angle), angularVelocity(0.f), angularAcceleration(0.f), mass(mass), momentOfInertia(inertia) {}
	RB2D() {}
};

class PendulumSystem {
public:
	FVector2D anchor;
	RB2D playerBob;
	float length;
	float damping;
	float motorSpeed;
	float maxMotorTorque;

	PendulumSystem(FVector2D anchorPoint, FVector2D bobPosition, float bobMass, 
		float rodLength, float dampingFactor) : anchor(anchorPoint), playerBob(bobPosition, 
			bobMass, 1.65f * bobMass * rodLength), length(rodLength), damping(dampingFactor), 
		motorSpeed(0.f), maxMotorTorque(250.0f) {}
	PendulumSystem(FVector2D anchorPoint, FVector2D bobPosition, float bobMass,
		float rodLength, float dampingFactor, float startAngle) : anchor(anchorPoint), playerBob(bobPosition,
			bobMass, 1.65f * bobMass * rodLength, startAngle), length(rodLength), damping(dampingFactor),
		motorSpeed(0.f), maxMotorTorque(250.0f) {}
	PendulumSystem() {}

	FVector GetPendulumAnchorPosition3D()
	{
		return FVector(anchor.X, -anchor.Y, 0.f);
	}

	FVector2D GetPendulumBobPosition2D()
	{
		// -y since game setup quirk (up decreases y, down increases y)
		return FVector2D(playerBob.position.X, -playerBob.position.Y);
	}

	FVector GetPendulumBobPosition3D()
	{
		return FVector(playerBob.position.X, -playerBob.position.Y, 0.f);
	}

	void Update(float deltaTime) {
		// Calculate direction and enforce hinge constraint
		FVector2D direction = playerBob.position - anchor;
		float distance = direction.Size();
		FVector2D normalizedDirection = direction / distance;

		// Setup pendulum & gravity
		playerBob.position = anchor + normalizedDirection * length;
		FVector2D gravity = FVector2D(0.0f, -GRAVITY) * playerBob.mass;

		// Project gravity onto the tangential direction
		FVector2D tangent(-normalizedDirection.Y, normalizedDirection.X);
		FVector2D tangentialForce = FVector2D::DotProduct(gravity, tangent) * tangent;
		tangentialForce *= 1.8f;

		// Compute torque from tangential force
		float torque = FVector2D::DotProduct(tangentialForce, tangent) * length;
		// Apply damping to angular velocity
		playerBob.angularVelocity *= FMath::Clamp(1.0f - damping * deltaTime, 0.f, 1.0f);
		// Update angular velocity from torque
		playerBob.angularVelocity += torque / playerBob.momentOfInertia * deltaTime;
		// Apply motor torque
		ApplyMotorTorque(deltaTime);

		// Update the angle of the pendulum
		playerBob.angle += playerBob.angularVelocity * deltaTime;
		// Update the pendulum position based on the new angle
		playerBob.position = anchor + FVector2D(FMath::Sin(playerBob.angle), -FMath::Cos(playerBob.angle)) * length;

		// Convert angular velocity into linear velocity
		FVector2D radialDirection = (playerBob.position - anchor).GetSafeNormal();
		FVector2D tangentialDirection(-radialDirection.Y, radialDirection.X);
		// Ensure velocity follows the arc of motion
		playerBob.velocity = tangentialDirection * (playerBob.angularVelocity * length);

		// Fix any small drift in position
		FVector2D offset = playerBob.position - anchor;
		float currentLength = offset.Size();
		if (!FMath::IsNearlyEqual(currentLength, length, 0.01f))
		{
			// Correct position
			playerBob.position = anchor + offset.GetSafeNormal() * length;

			// Project velocity onto tangential direction to prevent energy loss
			FVector2D radialDir = offset.GetSafeNormal();
			FVector2D tangentDir(-radialDir.Y, radialDir.X);
			playerBob.velocity = FVector2D::DotProduct(playerBob.velocity, tangentDir) * tangentDir;
		}
	}

	void ApplyMotorTorque(float deltaTime) {
		float desiredAngularVelocity = motorSpeed;  // Target motor speed
		float motorTorque = FMath::Clamp(desiredAngularVelocity - playerBob.angularVelocity,
			-maxMotorTorque, maxMotorTorque);
		playerBob.angularVelocity += motorTorque / playerBob.momentOfInertia * deltaTime;
	}

	void SetMotorSpeed(float speed) {
		motorSpeed = speed;
	}

	void SlowMotorSpeed(float slowRate = 2.0f)
	{
		if (motorSpeed > 0)
		{
			motorSpeed -= slowRate;
		}
		else if (motorSpeed < 0)
		{
			motorSpeed += slowRate;
		}
	}

private:
	void DebugEnergy() {
		// Calculate height of the bob relative to the anchor
		float height = anchor.Y - playerBob.position.Y;

		// Compute potential and kinetic energy
		float potentialEnergy = playerBob.mass * 9.81f * height;
		float kineticEnergy = 0.5f * playerBob.mass * playerBob.velocity.SizeSquared() +
			0.5f * playerBob.momentOfInertia * playerBob.angularVelocity * playerBob.angularVelocity;

		float totalEnergy = potentialEnergy + kineticEnergy;

		// Debug output
		UE_LOG(LogTemp, Warning, TEXT("Potential Energy: %f, Kinetic Energy: %f, Total Energy: %f"),
			potentialEnergy, kineticEnergy, totalEnergy);
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class PROJECTIMPETUS_API UGrappleTether : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrappleTether();

	// Logic implemented in BP
	UFUNCTION(BlueprintImplementableEvent, Category = "Tether")
	void DynamicTether();
	UFUNCTION(BlueprintImplementableEvent, Category = "Tether")
	void PendulumTether();
	UFUNCTION(BlueprintImplementableEvent, Category = "Tether")
	void FireGrappleTether();
	UFUNCTION(BlueprintImplementableEvent, Category = "Tether")
	void RetractGrappleTether();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tether")
	float GrappleLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tether")
	FVector PendulumPivotPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tether")
	float PendulumBounceCooldown = 0.18f;
	float TimeSincePendulumBounce = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum Gameplay")
	float BounceStrength = 2000.0f;

	void MyPendulumTether(float deltaTime);
	void PrepareMyPendulumTether(FVector2D playerPos);
	void SolveMyPendulumTether(float deltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	PendulumSystem pendulum;
	APlayerController* controller;		
};
