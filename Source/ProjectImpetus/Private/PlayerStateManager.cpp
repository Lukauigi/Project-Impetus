// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateManager.h"

void UPlayerStateManager::InitializeFSM(UPlayerBaseState* InitialState)
{
  CurrentState = InitialState;
  CurrentState->EnterState();
}

void UPlayerStateManager::ChangeState(UPlayerBaseState* NewState)
{
  CurrentState->ExitState();
  CurrentState = NewState;
  CurrentState->EnterState();  
}

void UPlayerStateManager::Update(float DeltaTime)
{
  CurrentState->UpdateState(DeltaTime);
}
