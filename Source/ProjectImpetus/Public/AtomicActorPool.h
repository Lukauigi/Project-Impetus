// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActorPool.h"
#include "PooledActor.h"
#include "AtomicActorPool.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIMPETUS_API AAtomicActorPool : public ABaseActorPool
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APooledActor> pooledActorDef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<APooledActor*> pooledActors;
};
