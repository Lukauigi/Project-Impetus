// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPendulumState.h"

void UPlayerPendulumState::EnterState()
{
	Super::EnterState();

	UE_LOG(LogTemp, Log, TEXT("Entering Pendulum State"));
}

void UPlayerPendulumState::ExitState()
{
	Super::ExitState();
	UE_LOG(LogTemp, Log, TEXT("Exiting Pendulum State"));
}

void UPlayerPendulumState::UpdateState(float DeltaTime)
{
	Super::UpdateState(DeltaTime);
	UE_LOG(LogTemp, Log, TEXT("Updating Pendulum State"));
}
