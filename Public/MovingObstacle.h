// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "baseObstacle.h"
#include "HitReactInterface.h"
#include "MovingObstacle.generated.h"
/**
 * 
 */
class APlayerChracter;

UCLASS()
class SHOOTERCPP_API AMovingObstacle : public AbaseObstacle,public IHitReactInterface
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	void movementFunction();
	virtual void reactToHit(APlayerCharacter* playerRef) override;
	void playSoundAndSpawnEffect(APlayerCharacter* characterRef, UParticleSystem* particleSystem, USoundBase* sound);
	virtual void Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;
	//virtual void GetDamage(float Damage) override;

	
protected:
	UPROPERTY(EditAnywhere)
	float accumulatedTime = 0.f;
	UPROPERTY(EditAnywhere)
	float amplitude = 500.f;
	//UPROPERTY(EditAnywhere)
	//FVector	MovementVector=FVector(100.f,0.f,0.f);
	UPROPERTY(EditAnywhere)
	FVector oscillationVector = FVector(0.f, 0.f, 25.f);
	UPROPERTY(EditAnywhere)
	double MovementSpeed =1.0000f; // represents how quickly this actor reaches the player;
	UPROPERTY(EditAnywhere)
	UParticleSystem* hitParticle; // effect to play when this actor hit by player;
	UPROPERTY(EditAnywhere)
	USoundBase* hitSound;  // this will be played after this actor hit by the player;

	

private:
	bool isHit = false;




};
