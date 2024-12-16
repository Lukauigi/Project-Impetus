// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPaperCharacter.h"
#include "PlayerStateManagerComponent.h"

void ATestPaperCharacter::ChangeState(UPlayerBaseState* NewState)
{
    m_PlayerFSM->SetCurrentState(RoamingState);
}

void ATestPaperCharacter::BeginPlay()
{
    //// Initialize the PlayerStateManager
    //auto PlayerStateManager = NewObject<UPlayerStateManagerComponent>(this, TEXT("PlayerStateManager"));
    //PlayerStateManager->RegisterComponent();

    //// Create states
    //RoamingState = NewObject<UPlayerRoamingState>(this);
    //TetheredState = NewObject<UPlayerTetheredState>(this);

    //// Set initial state
    //if (PlayerStateManager)
    //{
    //    PlayerStateManager->ChangeState(RoamingState, this);
    //}
}
