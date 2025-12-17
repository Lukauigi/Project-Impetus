// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeLink.h"
#include "PaperPooledActor.h"
#include "GameplayNode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIMPETUS_API AGameplayNode : public APaperPooledActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ANodeLink* prevLink;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ANodeLink* nextLink;
	
};
