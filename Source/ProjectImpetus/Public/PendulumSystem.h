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
	// init with starting angle
	RB2D(FVector2D pos, float mass, float inertia, float angle) : position(pos), velocity(0.f, 0.f),
		angle(angle), angularVelocity(0.f), angularAcceleration(0.f), mass(mass), momentOfInertia(inertia) {}
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
	void Init(const FVector2D BobPos, const FVector2D AnchorPos, 
		const float TetherLength, const float playerMass = 1.0f, const float inertia = 1.65f);
	void Update(const float DeltaTime);
	void SetMotorSpeed(const float Speed) { motorSpeed = Speed; }
	void SetIsActive(const bool IsActive) { isActive = IsActive; }
	void Bounce(const FVector Direction);
	void IterateTimeSinceBounce(const float DeltaTime);
	
	const FVector GetPendulumAnchorPosition3D();
	const FVector2D GetPendulumBobPosition2D();
	const FVector GetPendulumBobPosition3D();
	
	bool GetIsActive() const { return isActive; }
	float GetMotorSpeedFactor() const { return MotorSpeedFactor; }
	RB2D GetPlayerBob() const { return playerBob; }
	bool IsHitAllowed() const { return timeSincePendulumBounce >= PendulumBounceCooldown; }

private:
	void ApplyMotorTorque(const float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum", meta = (AllowPrivateAccess = "true"))
	float length;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum", meta = (AllowPrivateAccess = "true"))
	float damping = 0.02f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum", meta = (AllowPrivateAccess = "true"))
	float maxMotorTorque = 250.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum", meta = (AllowPrivateAccess = "true"))
	float PendulumBounceCooldown = 0.116f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum", meta = (AllowPrivateAccess = "true"))
	float BounceStrength = 2000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum", meta = (AllowPrivateAccess = "true"))
	float AngularVelocityMomentumLossFactor = 0.8f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum", meta = (AllowPrivateAccess = "true"))
	float MotorSpeedFactor = 75.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pendulum", meta = (AllowPrivateAccess = "true"))
	float motorSpeed = 75.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pendulum", meta = (AllowPrivateAccess = "true"))
	bool isActive = false;

	float timeSincePendulumBounce = 0.f;
	bool firstLatch = true;
	FVector2D anchor;
	FVector2D orientation;
	RB2D playerBob;
};
