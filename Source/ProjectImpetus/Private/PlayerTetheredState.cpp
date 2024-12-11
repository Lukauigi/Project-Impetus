// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTetheredState.h"

void UPlayerTetheredState::EnterState()
{
	UE_LOG(LogTemp, Log, TEXT("Entering Tethered State"));
}

void UPlayerTetheredState::ExitState()
{
	UE_LOG(LogTemp, Log, TEXT("Exiting Tethered State"));
}

void UPlayerTetheredState::UpdateState(float DeltaTime)
{
	UE_LOG(LogTemp, Log, TEXT("Updating Tethered State"));
}
