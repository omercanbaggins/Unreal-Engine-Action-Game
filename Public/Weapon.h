#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "Weapon.generated.h"

class ABaseCharacter;



UCLASS()
class SHOOTERCPP_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	AWeapon();
	virtual void Tick(float DeltaTime) override;
	//void DestroyEffect(); //when fired when this weapon is killed
	UPROPERTY()
	FTimerHandle timerhandle;


	UPROPERTY(EditDefaultsOnly)
	FName rowName;
	
	UPROPERTY(EditAnywhere)
	float timeForFiring;
	UPROPERTY(EditAnywhere)
	UParticleSystem* effect;
	UPROPERTY(EditAnywhere)
	USoundBase* sound;
	UPROPERTY(EditAnywhere)
	UAnimMontage* animToPlay; //it is used for attack animation; //every  weapon holds its own montage, 
	virtual void Attack();
	virtual void I_Interact(ABaseCharacter* OwnerPawn) override;
	UPROPERTY(EditAnywhere)
	FName socketName; //this property varies for different weapon types, 
	//it is changed for every weapons so that it is passed in method named interact;
protected:
	virtual void BeginPlay() override;
	int damage = 1;


	int gunTypeIndex = 0;
};