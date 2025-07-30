// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "./shootercpp/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon.h"
#include "MeleeWeapon.h"
#include "Item.h"
ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	TArray<AMusicTape*>musics;
	musicList = musics;

}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	UCharacterMovementComponent* movementComp = GetCharacterMovement();
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);


	//weapon = GetWorld()->SpawnActor<AWeapon>(weaponClass,FVector::ZeroVector, FRotator::ZeroRotator);
	


	
}


void ABaseCharacter::attack() {
	if (activeWeapon && !bKilled) {
		//weapon->Fire();

	}	

}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	
	*/
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void ABaseCharacter::Die() {
	if (health <= 0) {
		UAnimInstance* anim = GetMesh()->GetAnimInstance();
		anim->Montage_Play(montageToPlay);
		bKilled = 1;
		GetWorldTimerManager().ClearTimer(weaponTimerH);
		SetLifeSpan(5.f);
	}
}
void ABaseCharacter::addToHealth(float v)
{

	health -= v;
	Die();

}

void ABaseCharacter::reactToHit(APawn* playerRef,float dmg)
{
	addToHealth(dmg);
	if (!bKilled) {
		GetMesh()->GetAnimInstance()->Montage_Play(hitReactMontage);

	}

	//play montage
	
}

void ABaseCharacter::pauseFire() {
	GetWorldTimerManager().ClearTimer(weaponTimerH);

}
void ABaseCharacter::startTimer() {
	//GetWorldTimerManager().ClearTimer(weaponTimerH);
	FTimerDelegate timerDelagate = FTimerDelegate::CreateLambda([this]()->void {attack(); });
	GetWorldTimerManager().SetTimer(weaponTimerH, timerDelagate, 0.5f, true);
}

void ABaseCharacter::useSword() {
	

}
