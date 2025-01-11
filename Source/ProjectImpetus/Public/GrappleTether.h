// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrappleTether.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class PROJECTIMPETUS_API UGrappleTether : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrappleTether();

	UFUNCTION(BlueprintImplementableEvent, Category = "Tether")
	void DynamicTether();
	UFUNCTION(BlueprintImplementableEvent, Category = "Tether")
	void PendulumTether();
	UFUNCTION(BlueprintImplementableEvent, Category = "Tether")
	void FireGrappleTether();
	UFUNCTION(BlueprintImplementableEvent, Category = "Tether")
	void RetractGrappleTether();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tether")
	float GrappleLength;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
