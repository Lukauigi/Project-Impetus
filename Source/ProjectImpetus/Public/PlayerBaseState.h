// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
// Enhanced Input
#include "../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "PlayerBaseState.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTIMPETUS_API UPlayerBaseState : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "State")
	virtual void EnterState();

	UFUNCTION(BlueprintCallable, Category = "State")
	virtual void ExitState();

	UFUNCTION(BlueprintCallable, Category = "State")
	virtual void UpdateState(float DeltaTime);

	void InitState(UEnhancedInputLocalPlayerSubsystem* InputSubsystem, UEnhancedInputComponent* EnhancedInputComponent);

protected:
	UEnhancedInputLocalPlayerSubsystem* m_InputSubSystem;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* m_IMC;
	UEnhancedInputComponent* m_EnhancedInputComponent;
	
};
