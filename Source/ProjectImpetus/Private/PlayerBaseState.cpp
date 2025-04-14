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
    for (const FInputBindingHandle Handle : m_BoundHandles)
    {
        m_EnhancedInputComponent->RemoveBinding(Handle);
    }
}

void UPlayerBaseState::UpdateState(float DeltaTime)
{
    /*if (m_InputSubSystem) UE_LOG(LogTemp, Log, TEXT("SubSystem exists"));
    if (m_IMC) UE_LOG(LogTemp, Log, TEXT("IMC exists"));*/
    //if (m_EnhancedInputComponent) UE_LOG(LogTemp, Log, TEXT("Input Comp exists"));
}

void UPlayerBaseState::InitState(UEnhancedInputLocalPlayerSubsystem* InputSubsystem, UEnhancedInputComponent* EnhancedInputComponent, AActor* Player)
{
    UE_LOG(LogTemp, Log, TEXT("PlayerBaseState: Assign members"));
    this->m_InputSubSystem = InputSubsystem;
    this->m_EnhancedInputComponent = EnhancedInputComponent;
    this->m_Player = Player;
}
