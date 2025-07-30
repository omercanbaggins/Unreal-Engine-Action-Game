// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "./shootercpp/PlayerCharacter.h"
#include "./GameFramework/CharacterMovementComponent.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	player = Cast<ABaseCharacter>(TryGetPawnOwner());
	if(player) movementComp = player->GetCharacterMovement();

}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (movementComp && player) {
		velocity = movementComp->Velocity;
		VelocityX = velocity.X;
		isFalling = movementComp->IsFalling();
		isFlying = movementComp->IsFlying();
		state = player->state;
	}
}



