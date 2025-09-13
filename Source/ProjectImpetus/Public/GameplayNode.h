// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeLink.h"
#include "PooledActor.h"
#include "GameplayNode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIMPETUS_API AGameplayNode : public APooledActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ANodeLink* prevLink;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ANodeLink* nextLink;
	
};
