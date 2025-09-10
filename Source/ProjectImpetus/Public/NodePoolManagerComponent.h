// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AtomicActorPool.h"
#include "Components/ActorComponent.h"
#include "NodePoolManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTIMPETUS_API UNodePoolManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNodePoolManagerComponent();

	UFUNCTION(BlueprintCallable, Category = "Create")
	void CreateNodeLinkCombo();
	UFUNCTION(BlueprintCallable, Category = "Destroy")
	void DestroyNodeLinkCombo();
	UFUNCTION(BlueprintCallable, Category = "Create")
	void DestroyAll();
	UFUNCTION(BlueprintCallable, Category = "Update")
	void RedirectNodeLink();
	UFUNCTION(BlueprintCallable, Category = "Create")
	void DestroyNodeLink();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AAtomicActorPool* nodePool;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AAtomicActorPool* linkPool;
};
