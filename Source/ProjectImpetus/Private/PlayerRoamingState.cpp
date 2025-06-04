// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRoamingState.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "GrappleTether.h"

void UPlayerRoamingState::EnterState()
{
	Super::EnterState();
	UE_LOG(LogTemp, Log, TEXT("Entering Roaming State"));

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
				&UPlayerRoamingState::InitTether
			);
			m_BoundHandles.Add(Handle);
		}
	}
}

void UPlayerRoamingState::ExitState()
{
	Super::ExitState();
	UE_LOG(LogTemp, Log, TEXT("Exiting Roaming State"));
}

void UPlayerRoamingState::UpdateState(float DeltaTime)
{
	Super::UpdateState(DeltaTime);
	//UE_LOG(LogTemp, Log, TEXT("Updating Roaming State"));
}

void UPlayerRoamingState::InitTether(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("Tether func called"));
	UGrappleTether* GrappleTetherComponent = m_Player->GetComponentByClass<UGrappleTether>();
	GrappleTetherComponent->FireGrappleTether();
}
