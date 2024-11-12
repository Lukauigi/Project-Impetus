// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRoamingState.h"

void UPlayerRoamingState::EnterState()
{
  UE_LOG(LogTemp, Log, TEXT("Entering Roaming State"));
}

void UPlayerRoamingState::ExitState()
{
  UE_LOG(LogTemp, Log, TEXT("Exiting Roaming State"));
}

void UPlayerRoamingState::UpdateState(float DeltaTime)
{
  UE_LOG(LogTemp, Log, TEXT("Updating Roaming State"));
}
