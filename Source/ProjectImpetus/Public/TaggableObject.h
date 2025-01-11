// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/GameplayTags/Classes/GameplayTagContainer.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/GameplayTags/Classes/GameplayTagAssetInterface.h" // Include the interface header
#include "TaggableObject.generated.h"

UCLASS()
class PROJECTIMPETUS_API ATaggableObject : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATaggableObject();

	// Implement the GameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Gameplay Tag Container
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Tags")
	FGameplayTagContainer GameplayTags;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
