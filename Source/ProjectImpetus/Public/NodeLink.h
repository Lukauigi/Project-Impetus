// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PooledActor.h"
#include "PaperPooledActor.h"
#include "NodeLink.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIMPETUS_API ANodeLink : public APaperPooledActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector2D startPnt;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector2D endPnt;
	
};
