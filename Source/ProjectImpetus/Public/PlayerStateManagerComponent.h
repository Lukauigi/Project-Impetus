// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
// States
#include "PlayerBaseState.h"
#include "PlayerRoamingState.h"
#include "PlayerTetheredState.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	TSubclassOf<UPlayerRoamingState> RoamingStateClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	TSubclassOf<UPlayerTetheredState> TetheredStateClass;

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

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State Management", meta = (AllowPrivateAccess = "true"))
	UPlayerRoamingState* RoamingState;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State Management", meta = (AllowPrivateAccess = "true"))
	UPlayerTetheredState* TetheredState;
		
};
