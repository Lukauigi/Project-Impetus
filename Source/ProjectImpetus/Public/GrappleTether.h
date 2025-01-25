// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrappleTether.generated.h"

struct RB2D {
	FVector2D position;
	FVector2D velocity;
	float angle;
	float angularVelocity;
	float mass;
	float momentOfInertia;

	RB2D(FVector2D pos, float mass, float inertia) : position(pos), velocity(0.f, 0.f), 
		angle(0.f), angularVelocity(0.f), mass(mass), momentOfInertia(inertia) {}
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
			bobMass, 0.5f * bobMass * rodLength), length(rodLength), damping(dampingFactor), 
		motorSpeed(0.f), maxMotorTorque(10.0f) {}
	PendulumSystem() {}

	void Update(float deltaTime) {
		// Calculate direction and enforce hinge constraint
		FVector2D direction = playerBob.position - anchor;
		float distance = direction.Size();
		FVector2D normalizedDirection = direction / distance;

		// Keep pendulum at fixed length
		playerBob.position = anchor + normalizedDirection * length;

		// Apply gravity force
		FVector2D gravity = FVector2D(0.0f, -9.81f) * playerBob.mass;

		// Project gravity onto the tangential direction
		FVector2D tangent(-normalizedDirection.Y, normalizedDirection.X);
		FVector2D tangentialForce = FVector2D::DotProduct(gravity, tangent) * tangent;

		// Compute torque from tangential force
		float torque = FVector2D::DotProduct(tangentialForce, tangent) * length;

		// Apply damping to angular velocity
		playerBob.angularVelocity *= FMath::Clamp(1.0f - damping * deltaTime, 0.0f, 1.0f);

		// Update angular velocity from torque
		playerBob.angularVelocity += torque / playerBob.momentOfInertia * deltaTime;

		// Apply motor torque
		ApplyMotorTorque(deltaTime);

		// Update the angle of the pendulum
		playerBob.angle += playerBob.angularVelocity * deltaTime;

		// Update the pendulum position based on the new angle
		playerBob.position = anchor + FVector2D(FMath::Sin(playerBob.angle), -FMath::Cos(playerBob.angle)) * length;
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

	void MyPendulumTether(float deltaTime);
	void PrepareMyPendulumTether(FVector2D playerPos);
	void StartMyPendulumTether(FVector2D anchorPos, FVector2D playerPos);
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
