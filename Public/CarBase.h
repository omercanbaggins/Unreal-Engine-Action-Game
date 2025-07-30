// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "CarBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERCPP_API ACarBase : public AWheeledVehiclePawn
{
	GENERATED_BODY()
public:
	ACarBase();
	void move(float V);
	void steering(float V);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UChaosVehicleMovementComponent* VehicleMovement;
};
