// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PlayerStateManager.h"
#include "TestPaperCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTIMPETUS_API ATestPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	void ChangeState(UPlayerBaseState* NewState);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State Management")
	UPlayerStateManagerComponent m_PlayerFSM;

	UPROPERTY()
	UPlayerBaseState* RoamingState;

	UPROPERTY()
	UPlayerBaseState* TetheredState;

	virtual void BeginPlay() override;
};
