// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "HitReactInterface.h"
#include "./shootercpp/PlayerCharacter.h"
void AGun::BeginPlay() {
	Super::BeginPlay();
}
void AGun::setWeaponType(FName rowname) {  // to reach weapon attributes from datatable
	if (table) {
		tableInstance = table->FindRow<FWeaponInformation>(rowname, "asd", true);

		if (tableInstance) {
			timeForFiring = tableInstance->firingTime; //if auto fire is activated this will be change fire time
			sound = tableInstance->firingSound;
			effect = tableInstance->firingParticle;
			itemMesh->SetStaticMesh(tableInstance->weaponMesh);
			//GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
			//GetWorldTimerManager().SetTimer(timerhandle, this, &AWeapon::Fire, timeForFiring, true, timeForFiring);
			setDamage(tableInstance->damage); // all weapons have different damage constant,
		}
	}
	else {
		//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString("failed"), true);

	}
}
void AGun::Attack()
{
	FHitResult hitresults;

	FVector End;
	UGameplayStatics::PlaySound2D(this, sound); 
	FVector start = itemMesh->GetSocketTransform(FName("namlu")).GetLocation();
	DrawDebugBox(GetWorld(), start, FVector(5.5f), FColor::Red, false, 1.f);
	double socketYaw = itemMesh->GetSocketRotation(FName("namlu")).Yaw;
	FVector socketForward = FRotationMatrix(FRotator(0, socketYaw, 0)).GetUnitAxis(EAxis::Y);
	End = start + (socketForward*1000);
	//weapon will fire into its forward  this 1000 is used for adjust distance. It can be replaced with costant which can be rearanged from blueprint
	DrawDebugBox(GetWorld(), End, FVector(5.5f), FColor::Blue, true, 1.f);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), effect,start, GetActorRotation());
	//IHitReactInterface* hitActor;
	FCollisionQueryParams params;
	params.AddIgnoredActor(GetOwner());
	params.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(hitresults,start, End, ECollisionChannel::ECC_Visibility,params);
	DrawDebugLine(GetWorld(), GetActorLocation(), End, FColor::Red, true, 0.2f);
	//another interface to cast
	//hitActor = Cast<IHitReactInterface>(hitresults.GetActor());
	if (hitresults.bBlockingHit ) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), effect, hitresults.ImpactPoint, FRotator(0));
		APlayerCharacter* playerRef = Cast<APlayerCharacter>(GetAttachParentActor()); // check if this weapon was equipped by the player
		ABaseCharacter* hitactor = Cast<ABaseCharacter>(hitresults.GetActor());			GEngine->AddOnScreenDebugMessage(111144, 1.0f, FColor::Red, FString(hitresults.GetActor()->GetName()), true);

		if(hitactor) 
			hitactor->reactToHit(NULL,2.f);


	}
}
void AGun::setDamage(int d)
{
	if (d > 0)
		damage = d;
}