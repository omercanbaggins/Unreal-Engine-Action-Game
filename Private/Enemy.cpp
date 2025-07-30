// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/PawnSensingComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"
#include "Weapon.h"
#include "MeleeWeapon.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/CharacterMovementComponent.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	pawnDetector = CreateDefaultSubobject<UPawnSensingComponent>(FName("pawnSensingComp"));
	pathComp = CreateDefaultSubobject<UPathFollowingComponent>(FName("PathFollowing"));

}

void AEnemy::BeginPlay() {
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = UpdateMaxSpeed();

	/*
	AAIController* controller = Cast<AAIController>(GetController());
	if (controller) {
		controller->ReceiveMoveCompleted.AddDynamic(this, &AEnemy::OnMoveFinished);
	}
	*/


	pawnDetector->OnSeePawn.AddDynamic(this, &AEnemy::OnSeePawn);

	FTimerHandle tH;

	FTimerDelegate delagete = FTimerDelegate::CreateLambda([this]()->void {PatrolAndPursue(); });

	FTimerHandle attacktH;
	FTimerDelegate Attackdelagete = FTimerDelegate::CreateLambda([this]()->void {EnemyAttack(); });

	GetWorldTimerManager().SetTimer(tH, delagete, 2.f, true, 1.f);	
	//GetWorldTimerManager().SetTimer(attacktH, Attackdelagete, 2.f, true, 1.f);


	Patrol();
	activeWeapon = GetWorld()->SpawnActor<AWeapon>(weaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
	if (activeWeapon) {
		EAttachmentRule rule = EAttachmentRule::SnapToTarget;
		FAttachmentTransformRules atRules = FAttachmentTransformRules(rule, true);
		bool AttachmentResult = activeWeapon->AttachToComponent(GetMesh(), atRules, activeWeapon->socketName);
		if (AttachmentResult) {
			this->state = ECharacterStates::EEquippedWithMelee;
			activeWeapon->SetOwner(this);
		}
	}
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &AEnemy::print);

}

void AEnemy::PatrolAndPursue() {
	
	AAIController* controller = Cast<AAIController>(GetController());
	if (controller && !bKilled) {

		
		if (targetCharacter) {
			FVector vectorSubstraction = GetActorLocation() - targetCharacter->GetActorLocation();
			DistanceToEnemy = vectorSubstraction.Size();
			if (DistanceToEnemy > distanceThreshold) {
				loseInterest();
				GEngine->AddOnScreenDebugMessage(1256, 1.f, FColor::Red, FString("loseInterest"));
			}
			else if (DistanceToEnemy <= distanceThreshold && DistanceToEnemy > 200) {
				GEngine->AddOnScreenDebugMessage(1256, 1.f, FColor::Red, FString("ai goes to character"));
				Estate = EEnemyState::chasing;
				controller->MoveToActor(targetCharacter);
			}
					//GetMesh()->GetAnimInstance()->Montage_Play(weapon->animToPlay, 0.7f);
			else if (DistanceToEnemy < 200) {
				EnemyAttack();				
			}
			
		}
		else if (target) {
			Patrol();
			GEngine->AddOnScreenDebugMessage(1256, 1.f, FColor::Red, FString("ai is patrolling"));
			controller->MoveToActor(target,5.f);


		}
	}
}

void AEnemy::Patrol() {
	TArray<AActor*>patrolTargets;
	UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), patrolTargets);
	int numberOfTargetPoints = patrolTargets.Num();
	if (numberOfTargetPoints > 0) {
		int rand = UKismetMathLibrary::RandomInteger(numberOfTargetPoints);
		target = patrolTargets[rand];
	}

}
void AEnemy::print(UAnimMontage* Montage, bool bInterrupted) {
	bcanAttack = 1;

}
void AEnemy::OnSeePawn(APawn* Pawn) {
	//APlayerCharacter* playerpawn = Cast<APlayerCharacter>(Pawn);
	if (Pawn && !targetCharacter) {
		targetCharacter = Pawn;
		GEngine->AddOnScreenDebugMessage(1256, 1.f, FColor::Red, FString("the ai have seen something"));
		Estate = EEnemyState::chasing;	
		GetCharacterMovement()->MaxWalkSpeed = UpdateMaxSpeed();

	}
}
void  AEnemy::loseInterest() {
	targetCharacter = NULL;
	Estate = EEnemyState::patrol;
	GetCharacterMovement()->MaxWalkSpeed = UpdateMaxSpeed();
	//GetWorldTimerManager().ClearTimer(weaponTimerH);


}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (targetCharacter) {
		FVector vectorSubstraction = GetActorLocation() - targetCharacter->GetActorLocation();
		DistanceToEnemy = vectorSubstraction.Size();
	}
}
float AEnemy::UpdateMaxSpeed() {
	switch (Estate)
	{
	case EEnemyState::patrol:
		return 200.f;
	case EEnemyState::chasing:
		return 650.f;
	default:
		return 200.f;
	}
}

void AEnemy::EnemyAttack() {
		int rand = UKismetMathLibrary::RandomIntegerInRange(1, 3);
		FString str = FString(FName("Attack").ToString()) + FString::FromInt(rand);
		GEngine->AddOnScreenDebugMessage(12512, 1.f, FColor::Red, str);
		GetMesh()->GetAnimInstance()->Montage_Play(activeWeapon->animToPlay, 0.8f);
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName(str), activeWeapon->animToPlay);
		activeWeapon->Attack();
	
}

int AEnemy::CompareDistance(AActor* actor) {
	if(actor) {
		FVector vectorSubstraction = GetActorLocation() - actor->GetActorLocation();
		return vectorSubstraction.Size();
	}
	return 999;
}


/*
void AEnemy::OnMoveFinished(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (Result.Code == EPathFollowingResult::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy reached the target!"));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Enemy reached the target!"));

		// Maybe choose a new patrol point?
		Patrol();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy movement failed or was interrupted."));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Enemy movement failed!"));
	}
}

*/