// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
// States
#include "PlayerBaseState.h"
#include "PlayerRoamingState.h"
#include "PlayerTetheredState.h"
#include "PlayerPendulumState.h"
#include "PlayerNodeGenState.h"
// UE5 Plugins
//#include "PaperCharacter.h"
//#include "EnhancedInputComponent.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "PlayerStateManagerComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTIMPETUS_API UPlayerStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// State Setters, set in BP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	TSubclassOf<UPlayerRoamingState> RoamingStateClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	TSubclassOf<UPlayerTetheredState> TetheredStateClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	TSubclassOf<UPlayerPendulumState> PendulumStateClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	TSubclassOf<UPlayerNodeGenState> NodeGenStateClass;

	// Sets default values for this component's properties
	UPlayerStateManagerComponent();

	UFUNCTION(BlueprintCallable, Category = "State Management")
	UPlayerBaseState* GetCurrentState() const { return m_CurrentState; }

	UFUNCTION(BlueprintCallable, Category = "State Management")
	void SetCurrentState(UPlayerBaseState* NewState);

	UFUNCTION(BlueprintCallable, Category = "State Management")
	void InitFSM();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPlayerBaseState* m_CurrentState;
	APawn* m_Player;
	UEnhancedInputLocalPlayerSubsystem* m_InputSubSystem;
	UInputMappingContext* m_CurrentContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "States", meta = (AllowPrivateAccess = "true"))
	UPlayerRoamingState* RoamingState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "States", meta = (AllowPrivateAccess = "true"))
	UPlayerTetheredState* TetheredState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "States", meta = (AllowPrivateAccess = "true"))
	UPlayerPendulumState* PendulumState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "States", meta = (AllowPrivateAccess = "true"))
	UPlayerNodeGenState* NodeGenState;
		
};
