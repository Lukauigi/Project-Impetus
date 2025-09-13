// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PooledActor.generated.h"

UCLASS(Abstract, Blueprintable)
class PROJECTIMPETUS_API APooledActor : public APaperCharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APooledActor();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Events")
	void SetInUse(bool isInUse);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool inUse = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
