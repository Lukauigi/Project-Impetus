// Fill out your copyright notice in the Description page of Project Settings.


#include "TaggableObject.h"

// Sets default values
ATaggableObject::ATaggableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATaggableObject::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = GameplayTags; // Provide the tags stored in your container
}

// Called when the game starts or when spawned
void ATaggableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATaggableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

