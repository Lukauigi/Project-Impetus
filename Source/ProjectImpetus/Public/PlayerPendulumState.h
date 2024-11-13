// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"
#include "PlayerPendulumState.generated.h"

/**
 * Player state where grapple tether is locked and
   the player now behaves like a pendulum.
 */
UCLASS(Blueprintable)
class PROJECTIMPETUS_API UPlayerPendulumState : public UPlayerBaseState
{
	GENERATED_BODY()

public:
  virtual void EnterState() override;
  virtual void ExitState() override;
  virtual void UpdateState(float DeltaTime) override;
	
};
