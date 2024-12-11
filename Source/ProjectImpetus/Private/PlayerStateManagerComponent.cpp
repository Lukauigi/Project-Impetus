// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateManagerComponent.h"

// Sets default values for this component's properties
UPlayerStateManagerComponent::UPlayerStateManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UPlayerStateManagerComponent::SetCurrentState(UPlayerBaseState* NewState)
{
	m_CurrentState->ExitState();
	m_CurrentState = NewState;
	m_CurrentState->EnterState();
}

// Called when the game starts
void UPlayerStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerStateManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	m_CurrentState->UpdateState(DeltaTime);
}

