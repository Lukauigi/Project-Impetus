// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerNodeGenState.h"

void UPlayerNodeGenState::EnterState()
{
	Super::EnterState();
	UE_LOG(LogTemp, Log, TEXT("Entering Roaming State"));

	//const TArray<FEnhancedActionKeyMapping>& Mappings = m_IMC->GetMappings();
	//for (const FEnhancedActionKeyMapping& Mapping : Mappings)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("Mapping: Action %s, Key %s"), *Mapping.Action->GetName(), *Mapping.Key.ToString());
	//	if (Mapping.Action->GetFName() == "IA_Move") //rename
	//	{
	//		FInputBindingHandle Handle = m_EnhancedInputComponent->BindAction(
	//			Mapping.Action,
	//			ETriggerEvent::Triggered,
	//			this,
	//			//&UPlayerNodeGenState::InitTether
	//		);
	//		m_BoundHandles.Add(Handle);
	//	}
	//}
}

void UPlayerNodeGenState::ExitState()
{
	Super::ExitState();
	UE_LOG(LogTemp, Log, TEXT("Exiting Node Gen State"));
}

void UPlayerNodeGenState::UpdateState(float DeltaTime)
{
	Super::UpdateState(DeltaTime);
	UE_LOG(LogTemp, Log, TEXT("Updating Node Gen State"));
}
