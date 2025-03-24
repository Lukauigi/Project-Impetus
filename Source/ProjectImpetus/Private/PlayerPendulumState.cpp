// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPendulumState.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "GrappleTether.h"

void UPlayerPendulumState::EnterState()
{
	Super::EnterState();

	UE_LOG(LogTemp, Log, TEXT("Entering Pendulum State"));
	const TArray<FEnhancedActionKeyMapping>& Mappings = m_IMC->GetMappings();
	//FInputBindingHandle Handle;
	for (const FEnhancedActionKeyMapping& Mapping : Mappings)
	{
		UE_LOG(LogTemp, Log, TEXT("Mapping: Action %s, Key %s"), *Mapping.Action->GetName(), *Mapping.Key.ToString());
		if (Mapping.Action->GetFName() == "IA_GrappleTether")
		{
			FInputBindingHandle Handle = m_EnhancedInputComponent->BindAction(
				Mapping.Action,
				ETriggerEvent::Triggered,
				this,
				&UPlayerPendulumState::DisableTether
			);
			m_BoundHandles.Add(Handle);
		}

		if (Mapping.Action->GetFName() == "IA_PendulumMovement")
		{
			FInputBindingHandle Handle = m_EnhancedInputComponent->BindAction(
				Mapping.Action,
				ETriggerEvent::Triggered,
				this,
				&UPlayerPendulumState::HandlePendulumInput
			);
			m_BoundHandles.Add(Handle);
		}
	}

	this->m_GrappleTetherComponent = m_Player->GetComponentByClass<UGrappleTether>();
	m_GrappleTetherComponent->PrepareMyPendulumTether(m_Player->GetActorLocation(), m_GrappleTetherComponent->CurrGrappleLength);
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
	m_GrappleTetherComponent->MyPendulumTether(DeltaTime);
}

void UPlayerPendulumState::DisableTether(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("TState has heard binded action"));
	m_GrappleTetherComponent->RetractGrappleTether();
}

void UPlayerPendulumState::HandlePendulumInput(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();
	//UE_LOG(LogTemp, Log, TEXT("PState Move Input: %f"), AxisValue);
	m_GrappleTetherComponent->PendulumPlayerInput(AxisValue);
}
