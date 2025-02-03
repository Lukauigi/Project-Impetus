// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "CustomPaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIMPETUS_API ACustomPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision Events")
	bool HasCollided = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
