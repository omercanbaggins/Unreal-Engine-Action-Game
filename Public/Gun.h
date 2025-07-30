// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Gun.generated.h"

UENUM()
enum class containedWeapon :uint32 {
	gun_normal = 1,
	gun_tank,
	gun_auto
};

USTRUCT()
struct FWeaponInformation :public FTableRowBase {
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* weaponMesh;

	UPROPERTY(EditDefaultsOnly)
	float firingTime;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* firingParticle;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* firingSound;

	UPROPERTY(EditDefaultsOnly)
	int damage;
};


UCLASS()
class SHOOTERCPP_API AGun : public AWeapon
{
	GENERATED_BODY()

public:
	FWeaponInformation* tableInstance;

	UPROPERTY(EditAnywhere)
	UDataTable* table;
	UPROPERTY(EditAnywhere)
	UBoxComponent* weaponFront;
	virtual void Attack() override;

private:

	void setDamage(int d);
	void setWeaponType(FName rowname);
	virtual void BeginPlay() override;

};
	
