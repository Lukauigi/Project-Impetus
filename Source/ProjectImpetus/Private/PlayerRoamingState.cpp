// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRoamingState.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"

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

			m_EnhancedInputComponent->BindAction(Mapping.Action, ETriggerEvent::Triggered, this, &UPlayerRoamingState::Tether);
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

	UE_LOG(LogTemp, Log, TEXT("Updating Roaming State"));
}

void UPlayerRoamingState::Tether(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("Tether func called"));
	//UFunction* func = m_Player->FindFunction(FName("DynamicTest"));
	UActorComponent* GrappleTetherComp = nullptr;

	for (UActorComponent* Component : m_Player->GetComponents())
	{
		if (Component->ComponentHasTag(FName("GrappleTether")))
		{
			GrappleTetherComp = Component;
			break;
		}
	}

	if (GrappleTetherComp)
	{
		UE_LOG(LogTemp, Log, TEXT("Inside scope"));
		UFunction* Function = GrappleTetherComp->FindFunction(FName("FireGrappleTether"));
		if (Function) GrappleTetherComp->ProcessEvent(Function, nullptr);
	}
}
