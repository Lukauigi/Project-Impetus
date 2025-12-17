// Fill out your copyright notice in the Description page of Project Settings.


#include "NodePoolManagerComponent.h"

// Sets default values for this component's properties
UNodePoolManagerComponent::UNodePoolManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UNodePoolManagerComponent::CreateNodeLinkCombo()
{
	// get node & link from pool
	// set node pos to player pos
	// set node link startPnt to player pos
	// set node link to node's prev link or nextLink
}

void UNodePoolManagerComponent::DestroyNodeLinkCombo()
{
}

void UNodePoolManagerComponent::DestroyAll()
{
}

void UNodePoolManagerComponent::RedirectNodeLink()
{
}

void UNodePoolManagerComponent::DestroyNodeLink()
{
}


// Called when the game starts
void UNodePoolManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNodePoolManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

