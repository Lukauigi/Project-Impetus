// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerBaseState.h"
#include "PlayerStateManager.generated.h"

/**
 * Controller of the state of the Player.
 */
UCLASS(Blueprintable)
class PROJECTIMPETUS_API UPlayerStateManager : public UObject
{
	GENERATED_BODY()

public:
  UPROPERTY(BlueprintReadOnly, Category = "State")
  UPlayerBaseState* CurrentState;

  UFUNCTION(BlueprintCallable, Category = "State")
  void InitializeFSM(UPlayerBaseState* InitialState);

  UFUNCTION(BlueprintCallable, Category = "State")
  void ChangeState(UPlayerBaseState* NewState);

  UFUNCTION(BlueprintCallable, Category = "State")
  void Update(float DeltaTime);

};
