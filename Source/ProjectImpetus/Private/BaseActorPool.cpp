// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActorPool.h"

// Sets default values
ABaseActorPool::ABaseActorPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

APooledActor* ABaseActorPool::AcquireFromPool()
{
	return nullptr;
}

bool ABaseActorPool::ReturnToPool()
{
	return false;
}

// Called when the game starts or when spawned
void ABaseActorPool::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseActorPool::InitPool()
{
}

// Called every frame
void ABaseActorPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

