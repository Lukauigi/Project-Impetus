// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTetheredState.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"

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
				&UPlayerTetheredState::RetractTether
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

void UPlayerTetheredState::RetractTether(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("TState has heard binded action"));
}
