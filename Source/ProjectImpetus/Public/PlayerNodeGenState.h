// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"
#include "PlayerNodeGenState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIMPETUS_API UPlayerNodeGenState : public UPlayerBaseState
{
	GENERATED_BODY()

public:
	virtual void EnterState() override;
	virtual void ExitState() override;
	virtual void UpdateState(float DeltaTime) override;
};
