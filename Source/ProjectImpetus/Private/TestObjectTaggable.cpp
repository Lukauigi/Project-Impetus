// Fill out your copyright notice in the Description page of Project Settings.


#include "TestObjectTaggable.h"

// Sets default values
ATestObjectTaggable::ATestObjectTaggable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATestObjectTaggable::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = GameplayTags; // Provide the tags stored in your container
}

// Called when the game starts or when spawned
void ATestObjectTaggable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestObjectTaggable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

