// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"
#include "PlayerRoamingState.generated.h"

/**
 * Player state where player is free to roam unrestricted. The default state.
 */
UCLASS(Blueprintable)
class PROJECTIMPETUS_API UPlayerRoamingState : public UPlayerBaseState
{
	GENERATED_BODY()

public:
  virtual void EnterState() override;
  virtual void ExitState() override;
  virtual void UpdateState(float DeltaTime) override;
	
};
