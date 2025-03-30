// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PendulumSystem.generated.h"

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
	RB2D() {}
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTIMPETUS_API UPendulumSystem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum")
	float length;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum")
	float damping = 0.02f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum")
	float motorSpeed = 75.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum")
	float maxMotorTorque = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pendulum")
	bool isActive = true;
	float TimeSincePendulumBounce = 0.f; //go private
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum")
	float PendulumBounceCooldown = 0.016f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum")
	float BounceStrength = 2000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum")
	float AngularVelocityMomentumLossFactor = 0.8f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum")
	float MotorSpeedFactor = 75.0f;

	void Init(const FVector2D BobPos, const FVector2D AnchorPos, 
		const float TetherLength);
	void Update(const float DeltaTime);
	void SetMotorSpeed(const float Speed) { motorSpeed = Speed; }
	void Bounce(const FVector Direction);
	void IterateTimeSinceBounce(const float DeltaTime);
	
	const FVector GetPendulumAnchorPosition3D();
	const FVector2D GetPendulumBobPosition2D();
	const FVector GetPendulumBobPosition3D();

	RB2D GetPlayerBob() const { return playerBob; }
	bool IsHitAllowed() const { return TimeSincePendulumBounce >= PendulumBounceCooldown; }

private:
	void ApplyMotorTorque(const float DeltaTime);

	bool firstLatch = true;
	FVector2D anchor;
	FVector2D orientation;
	RB2D playerBob;
};
