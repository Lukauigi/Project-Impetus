// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PooledActor.h"
#include "PaperCharacter.h"
#include "BaseActorPool.generated.h"

UCLASS(Abstract, Blueprintable)
class PROJECTIMPETUS_API ABaseActorPool : public APaperCharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActorPool();

	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual APooledActor* AcquireFromPool();
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual bool ReturnToPool();
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void InitPool();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pool", meta = (AllowPrivateAccess = "true"))
	int initPoolSize;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pool", meta = (AllowPrivateAccess = "true"))
	int maxPoolSize;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
