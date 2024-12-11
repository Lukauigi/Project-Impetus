// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPaperCharacter.h"

void ATestPaperCharacter::ChangeState(UPlayerBaseState* NewState)
{
    m_PlayerFSM.SetCurrentState(RoamingState);
}

void ATestPaperCharacter::BeginPlay()
{
    // Initialize the PlayerStateManager
    PlayerStateManager = NewObject<UPlayerStateManager>(this, TEXT("PlayerStateManager"));
    PlayerStateManager->RegisterComponent();

    // Create states
    RoamingState = NewObject<UPlayerRoamingState>(this);
    TetheredState = NewObject<UPlayerTetheredState>(this);

    // Set initial state
    if (PlayerStateManager)
    {
        PlayerStateManager->ChangeState(RoamingState, this);
    }
}
