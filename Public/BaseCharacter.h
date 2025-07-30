// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "./shootercpp/characterStates.h"
#include "BaseCharacter.generated.h"

struct FAIRequestID;
struct FPathFollowingResult;
class AWeapon;
class AMusicTape;

UENUM(Blueprintable)
enum class EEnemyState :uint8 {
	patrol = 0,
	waits,
	chasing,
	fight,
	killed
};

UCLASS()
class SHOOTERCPP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

	bool bcanAttack = true;

public:	

	UPROPERTY(BlueprintReadOnly)
	bool bKilled = 0;


	//void MoveComp(FAIRequestID RequestID, FPathFollowingResult& Result);

	void attack();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Die();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float health=20.f;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	double distanceThreshold = (double)300;
	virtual void addToHealth(float v);
	

	UFUNCTION(BlueprintCallable)
	void reactToHit(APawn* playerRef,float dmg);
	void pauseFire();
	void startTimer();
	void useSword();
	//virtual void reactToHit(APlayerCharacter* playerRef) override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* montageToPlay;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)

	EEnemyState Estate = EEnemyState::patrol;

	ECharacterStates state = ECharacterStates::EUnequipped;
	class UPathFollowingComponent* pathComp;
	UPROPERTY()
	AWeapon* activeWeapon;

	UFUNCTION(BlueprintCallable)
	AWeapon* getActiveWeapon() const {
		return activeWeapon;

	}


	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> weaponClass;

	FTimerHandle weaponTimerH;
	UPROPERTY(EditAnywhere)

	UAnimMontage* hitReactMontage;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float damage=2.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AMusicTape*> musicList;

};
