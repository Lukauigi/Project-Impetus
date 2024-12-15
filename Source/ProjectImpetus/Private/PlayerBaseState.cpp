// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseState.h"
#include "Components/ActorComponent.h"

void UPlayerBaseState::EnterState()
{
    this->m_InputSubSystem->AddMappingContext(m_IMC, 0);
}

void UPlayerBaseState::ExitState()
{
    this->m_InputSubSystem->ClearAllMappings();
}

void UPlayerBaseState::UpdateState(float DeltaTime)
{
}

void UPlayerBaseState::InitState(UEnhancedInputLocalPlayerSubsystem* InputSubsystem)
{
    UE_LOG(LogTemp, Log, TEXT("PlayerBaseState: Assign member"));
    this->m_InputSubSystem = InputSubsystem;
}
