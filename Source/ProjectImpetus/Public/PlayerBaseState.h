// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerBaseState.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTIMPETUS_API UPlayerBaseState : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "State")
	virtual void EnterState() PURE_VIRTUAL(UPlayerBaseState::EnterState, );

	UFUNCTION(BlueprintCallable, Category = "State")
	virtual void ExitState() PURE_VIRTUAL(UPlayerBaseState::ExitState, );

	UFUNCTION(BlueprintCallable, Category = "State")
	virtual void UpdateState(float DeltaTime) PURE_VIRTUAL(UPlayerBaseState::UpdateState, );
	
};
