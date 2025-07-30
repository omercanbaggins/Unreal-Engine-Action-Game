// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "./shootercpp/characterStates.h"
#include "PlayerCharacter.generated.h"
class UUCharacterStat;
class AItem;
UCLASS()
class SHOOTERCPP_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FTimerHandle weaponTimerH;
	bool bPressed;

	

public:	
	APlayerCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void lookRight(float Value);
	void lookUp(float Value);
	void MoveRight(float Value);
	//class AWeapon* weapon;
	void Attack();
	UFUNCTION(BlueprintCallable)
	void Interact();
	void performAttack();
	void pauseFire();
	UFUNCTION()
	void Move(float V);
	class USphereComponent* sphere;
	UFUNCTION()
	void overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UCapsuleComponent* capsule;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)

	ECharacterStates state = ECharacterStates::EUnequipped;

	
	TArray<AItem*> inventory;
	UFUNCTION(BlueprintCallable)
	void useItem();

	void addToHealth(float v) override;

	void calculateDamage();


	UPROPERTY(BlueprintReadWrite)
	class UCharacterStatComponent* statComp;


};
