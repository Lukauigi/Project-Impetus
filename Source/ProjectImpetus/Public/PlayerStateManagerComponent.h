// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerBaseState.h"
#include "PlayerStateManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTIMPETUS_API UPlayerStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStateManagerComponent();

	UFUNCTION(BlueprintCallable, Category = "State Management")
	UPlayerBaseState* GetCurrentState() { return m_CurrentState; }

	UFUNCTION(BlueprintCallable, Category = "State Management")
	void SetCurrentState(UPlayerBaseState* NewState);

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPlayerBaseState* m_CurrentState;

		
};
