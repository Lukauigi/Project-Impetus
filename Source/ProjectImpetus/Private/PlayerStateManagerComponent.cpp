// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateManagerComponent.h"
#include "PlayerRoamingState.h"
#include "PlayerTetheredState.h"
//#include "EnhancedInputSubsystems.h"

// Sets default values for this component's properties
UPlayerStateManagerComponent::UPlayerStateManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	this->RoamingState = CreateDefaultSubobject<UPlayerRoamingState>(TEXT("RoamingState"));
	this->TetheredState = CreateDefaultSubobject<UPlayerTetheredState>(TEXT("TetheredState"));
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

void UPlayerStateManagerComponent::InitFSM()
{
	UE_LOG(LogTemp, Log, TEXT("Get Pawn!!!"));
	this->m_Player = Cast<APawn>(GetOwner());
	if (m_Player)
	{
		UE_LOG(LogTemp, Log, TEXT("Get PlayerController"));
		// Get the player controller
		APlayerController* PlayerController = Cast<APlayerController>(m_Player->GetController());
		if (!PlayerController) return;

		// Get the local player
		UE_LOG(LogTemp, Log, TEXT("Get LocalPlayer"));
		ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		if (!LocalPlayer) return;

		// Get the Enhanced Input subsystem
		UE_LOG(LogTemp, Log, TEXT("Get InputSubSystem"));
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (!InputSubsystem) return;

		UE_LOG(LogTemp, Log, TEXT("We got the IMC??? Let's try clearing it."));
		this->m_InputSubSystem = InputSubsystem;

		this->RoamingState->InitState(m_InputSubSystem);
		this->TetheredState->InitState(m_InputSubSystem);

		this->m_CurrentState = this->RoamingState;
		this->m_CurrentState->EnterState();
	}
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
	//m_CurrentState->UpdateState(DeltaTime);
}

