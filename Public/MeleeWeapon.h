// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Weapon.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERCPP_API AMeleeWeapon : public AWeapon
{

	GENERATED_BODY()
public:

	AMeleeWeapon();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Attack() override;
	void TraceForAttack();
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UPROPERTY(EditAnywhere)
	USceneComponent* start;
	UPROPERTY(EditAnywhere)
	USceneComponent* end;
	

	//it will be updated using datatable
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UBoxComponent* boxForTrace;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)

	TArray<AActor*> hitActors;

};
