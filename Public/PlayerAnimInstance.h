// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "./shootercpp/characterStates.h"
#include "PlayerAnimInstance.generated.h"

class ABaseCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class SHOOTERCPP_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	FVector velocity;
	UPROPERTY(BlueprintReadOnly)
	double VelocityX;

	UPROPERTY(BlueprintReadOnly)
	ABaseCharacter* player;
	UPROPERTY(BlueprintReadOnly)
	UCharacterMovementComponent* movementComp;

	
	UPROPERTY(BlueprintReadOnly)
	bool isFalling;
	UPROPERTY(BlueprintReadOnly)
	bool isFlying;
	UPROPERTY(BlueprintReadOnly)
	ECharacterStates state;

};
