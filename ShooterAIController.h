// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:

	class APawn* PlayerPawn;

	UPROPERTY(EditAnywhere)
	float FocusDistance = 500;

	// Replaced by Behavior Tree
	// UPROPERTY(EditAnywhere)
	// float AcceptanceRadius = 300;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

};
