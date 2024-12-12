// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateManagerComponent.h"
#include "PlayerRoamingState.h"
#include "PlayerTetheredState.h"

// Sets default values for this component's properties
UPlayerStateManagerComponent::UPlayerStateManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	this->RoamingState = CreateDefaultSubobject<UPlayerRoamingState>(TEXT("RoamingState"));
	this->TetheredState = CreateDefaultSubobject<UPlayerTetheredState>(TEXT("TetheredState"));
	this->m_CurrentState = this->RoamingState;
}

void UPlayerStateManagerComponent::SetCurrentState(UPlayerBaseState* NewState)
{
	if (m_CurrentState != NewState)
	{
		m_CurrentState->ExitState();
		m_CurrentState = NewState;
		m_CurrentState->EnterState();
	}
}

// Called when the game starts
void UPlayerStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// If RoamingState is assigned via Blueprint or editor, set m_CurrentState
	if (RoamingState)
	{
		//this->m_CurrentState = RoamingState;
		this->m_CurrentState->EnterState();
		UE_LOG(LogTemp, Log, TEXT("SetCurrentState - RoamingState is set!"));
	}
	else
	{
		// Handle the case where RoamingState is not set (optional)
		UE_LOG(LogTemp, Log, TEXT("RoamingState is not set!"));
	}
}


// Called every frame
void UPlayerStateManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//m_CurrentState->UpdateState(DeltaTime);
}

