// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingObstacle.h"
#include "Kismet/KismetMathLibrary.h"
#include "./shootercpp/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "./Components/SphereComponent.h"

void AMovingObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	accumulatedTime += DeltaTime;
	movementFunction();
}

void AMovingObstacle::BeginPlay()
{
	Super::BeginPlay();	
	sphere->OnComponentBeginOverlap.RemoveDynamic(this, &Super::Overlap);

	sphere->OnComponentBeginOverlap.AddDynamic(this, &AMovingObstacle::Overlap);

}

void AMovingObstacle::movementFunction()
{
	double sinParamater = 2 * PI*accumulatedTime;
	double result = amplitude* UKismetMathLibrary::Sin(sinParamater);
	FVector vectorToAdd = oscillationVector * result; // it will make oscillation movement means it will go up down (movement in Z axis);
	AddActorLocalOffset(vectorToAdd);
	//GEngine->AddOnScreenDebugMessage(1,0.1,f)
	FHitResult hr;
	AddActorLocalOffset(MovementSpeed*GetActorForwardVector(),false, &hr ,ETeleportType::TeleportPhysics); // it'll go towards the player in X axis, this actor has to be placed in a way that the player faces to this actor

}
void AMovingObstacle::reactToHit(APlayerCharacter* playerRef) {
	if (playerRef) {
		
		mesh->SetSimulatePhysics(true); mesh->AddForce(FVector(0.f, 0.f, 150000.f));
		mesh->SetEnableGravity(true);
		playSoundAndSpawnEffect(playerRef,hitParticle,hitSound);
		SetLifeSpan(4.25f);
		GEngine->AddOnScreenDebugMessage(1245, 1.f, FColor::Red, FString("asd"));
		isHit = 1;
	}


}
void AMovingObstacle::playSoundAndSpawnEffect(APlayerCharacter* characterRef, UParticleSystem* particleSystem, USoundBase* sound) {
	if (characterRef) {
		
		FVector spawnVectorForEmitter = mesh->GetComponentLocation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particleSystem, mesh->GetComponentTransform());
		UGameplayStatics::PlaySound2D(this, sound);
	}
};


void AMovingObstacle::Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (isHit) {
		Super::Overlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}
