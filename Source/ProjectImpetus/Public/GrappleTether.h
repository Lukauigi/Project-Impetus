// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PendulumSystem.h"
#include "GrappleTether.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class PROJECTIMPETUS_API UGrappleTether : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrappleTether();

	// Logic implemented in BP
	UFUNCTION(BlueprintImplementableEvent, Category = "Tether")
	void DynamicTether();
	UFUNCTION(BlueprintImplementableEvent, Category = "Tether")
	void PendulumTether();
	UFUNCTION(BlueprintImplementableEvent, Category = "Tether")
	void FireGrappleTether();
	UFUNCTION(BlueprintImplementableEvent, Category = "Tether")
	void RetractGrappleTether();
	UFUNCTION(BlueprintImplementableEvent, Category = "Tether")
	void UpdateTetherVisual_CPP_Var(FVector PlayerPos, FVector PendulumAnchorPos);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tether")
	float MaxGrappleLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tether")
	float CurrGrappleLength = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tether")
	FVector PendulumPivotPoint;

	void MyPendulumTether(float deltaTime);
	void PrepareMyPendulumTether(FVector playerPos, float tetherLength);
	void SolveMyPendulumTether(float deltaTime);
	void PendulumPlayerInput(float axisValue);
	void DisablePendulum() { uPendulumSystem->SetIsActive(false); }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum", meta = (AllowPrivateAccess = "true"))
	UPendulumSystem* uPendulumSystem;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pendulum", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPendulumSystem> PendulumSystemClass;
	float input;
};

//USTRUCT(BlueprintType)
//struct TetherUpdateParams
//{
//	GENERATED_BODY()
//
//	UPROPERTY(BlueprintReadWrite)
//	FVector PlayerPos;
//
//	UPROPERTY(BlueprintReadWrite)
//	FVector PendulumAnchorPos;
//};
