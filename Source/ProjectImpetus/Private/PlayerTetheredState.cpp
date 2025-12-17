// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTetheredState.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "GrappleTether.h"
#include "CustomPaperCharacter.h"

void UPlayerTetheredState::EnterState()
{
	Super::EnterState();

	UE_LOG(LogTemp, Log, TEXT("Entering Tethered State"));
	const TArray<FEnhancedActionKeyMapping>& Mappings = m_IMC->GetMappings();
	for (const FEnhancedActionKeyMapping& Mapping : Mappings)
	{
		UE_LOG(LogTemp, Log, TEXT("Mapping: Action %s, Key %s"), *Mapping.Action->GetName(), *Mapping.Key.ToString());
		if (Mapping.Action->GetFName() == "IA_GrappleTether")
		{
			FInputBindingHandle Handle = m_EnhancedInputComponent->BindAction(
				Mapping.Action, 
				ETriggerEvent::Triggered, 
				this, 
				&UPlayerTetheredState::DisableTether
			);
			m_BoundHandles.Add(Handle);
		}
		// bind function to GenerateNode
		if (Mapping.Action->GetFName() == "IA_GenerateNode")
		{
			FInputBindingHandle Handle = m_EnhancedInputComponent->BindAction(
				Mapping.Action,
				ETriggerEvent::Triggered,
				this,
				&UPlayerTetheredState::TransitionToNodeGen
			);
			m_BoundHandles.Add(Handle);
		}
	}
}

void UPlayerTetheredState::ExitState()
{
	Super::ExitState();
	UE_LOG(LogTemp, Log, TEXT("Exiting Tethered State"));
}

void UPlayerTetheredState::UpdateState(float DeltaTime)
{
	Super::UpdateState(DeltaTime);
	UE_LOG(LogTemp, Log, TEXT("Updating Tethered State"));
}

void UPlayerTetheredState::DisableTether(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("TState has heard binded action"));
	UGrappleTether* GrappleTetherComponent = m_Player->GetComponentByClass<UGrappleTether>();
	GrappleTetherComponent->RetractGrappleTether();
}

void UPlayerTetheredState::TransitionToNodeGen(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("TState has heard TransitionToNodeGen binded action"));
	// need to call a func that will change state to PlayerNodeGen
	ACustomPaperCharacter* p = Cast<ACustomPaperCharacter>(m_Player);
	p->ActivateNodeGeneration();
}
