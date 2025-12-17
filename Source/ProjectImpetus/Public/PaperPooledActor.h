// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "PaperPooledActor.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTIMPETUS_API APaperPooledActor : public APaperSpriteActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Events")
	void SetInUse(bool isInUse);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool inUse = false;
};
