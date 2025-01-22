// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPendulumState.h"

void UPlayerTetheredState::EnterState()
{
	Super::EnterState();

	UE_LOG(LogTemp, Log, TEXT("Entering Pendulum State"));
}

void UPlayerTetheredState::ExitState()
{
	Super::ExitState();
	UE_LOG(LogTemp, Log, TEXT("Exiting Pendulum State"));
}

void UPlayerTetheredState::UpdateState(float DeltaTime)
{
	Super::UpdateState(DeltaTime);
	UE_LOG(LogTemp, Log, TEXT("Updating Pendulum State"));
}
