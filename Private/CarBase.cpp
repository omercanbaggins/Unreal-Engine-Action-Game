// Fill out your copyright notice in the Description page of Project Settings.


#include "CarBase.h"
#include "ChaosVehicleMovementComponent.h"

ACarBase::ACarBase() {
	VehicleMovement = GetVehicleMovementComponent();
}
void ACarBase::move(float V) {
	GetVehicleMovementComponent()->SetThrottleInput(V);
	GEngine->AddOnScreenDebugMessage(901, 0.2f, FColor::Red, FString("throttling")+FString::SanitizeFloat(V));
}
void ACarBase::steering(float V) {
	GetVehicleMovementComponent()->SetThrottleInput(V);
	GEngine->AddOnScreenDebugMessage(902, 0.2f, FColor::Red, FString("steeringgg") + FString::SanitizeFloat(V));

}

void ACarBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("move", this, &ACarBase::move);
	PlayerInputComponent->BindAxis("right", this, &ACarBase::steering);	

}
