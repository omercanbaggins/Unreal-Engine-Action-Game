// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
//#include "AIController.h"
#include "Enemy.generated.h"



UCLASS()
class SHOOTERCPP_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()
public:

	AEnemy();

	void BeginPlay();

	void PatrolAndPursue();

	void Patrol();
	UFUNCTION()
	void print(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnSeePawn(APawn* Pawn);

	void loseInterest();

	virtual void Tick(float DeltaTime) override;

	float UpdateMaxSpeed();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	double DistanceToEnemy = (double)0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UPawnSensingComponent* pawnDetector;

	APawn* targetCharacter; 
	AActor* target;

	void EnemyAttack();

	int CompareDistance(AActor* actor);


	/*
	UFUNCTION()
	void OnMoveFinished(FAIRequestID RequestID, const FPathFollowingResult& Result);
	*/

};
