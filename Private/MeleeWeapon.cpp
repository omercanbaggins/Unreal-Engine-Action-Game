// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "./shootercpp/PlayerCharacter.h"
AMeleeWeapon::AMeleeWeapon() {
	end = CreateDefaultSubobject<USceneComponent>(FName("weaponEnd"));
	start = CreateDefaultSubobject<USceneComponent>(FName("weaponStart"));
	boxForTrace = CreateDefaultSubobject<UBoxComponent>(FName("boxForTrace"));
	boxForTrace->SetupAttachment(itemMesh);
	end->SetupAttachment(itemMesh);
	start->SetupAttachment(itemMesh);

}
void AMeleeWeapon::BeginPlay() {
	Super::BeginPlay();
	boxForTrace->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::BeginOverlap);
	boxForTrace->OnComponentEndOverlap.AddDynamic(this, &AMeleeWeapon::EndOverlap);
	boxForTrace->SetGenerateOverlapEvents(false);

	
}
void AMeleeWeapon::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//TraceForAttack();
}
void AMeleeWeapon::Attack() {
	//boxForTrace->SetGenerateOverlapEvents(true);
	//ABaseCharacter* pawn = Cast<ABaseCharacter>(GetOwner());

	//TraceForAttack();

}
void AMeleeWeapon::TraceForAttack() {
	ABaseCharacter* pawn = Cast<ABaseCharacter>(GetOwner());
	if (pawn) {
		GEngine->AddOnScreenDebugMessage(14112, 1.0f, FColor::Red, FString("item was used to attack"));

		FHitResult hitresults;
		FVector startLoc = start->GetComponentLocation();
		FVector EndLoc = end->GetComponentLocation();

		TArray<AActor*> actorsToIgnore; actorsToIgnore.Add(this->GetOwner());
		for (AActor* actor : hitActors) {
			actorsToIgnore.AddUnique(actor);
		}
		FRotator oriantation = FVector(start - end).Rotation();
		UKismetSystemLibrary::BoxTraceSingle(this, startLoc, EndLoc, FVector(5.f),
			oriantation, UEngineTypes::ConvertToTraceType(ECC_Visibility)
			, false, actorsToIgnore, EDrawDebugTrace::Persistent, hitresults, true);
		ABaseCharacter* player = Cast<ABaseCharacter>(hitresults.GetActor());
		if (hitresults.bBlockingHit) { DrawDebugBox(GetWorld(), hitresults.ImpactPoint, FVector(1), FColor::Magenta, true); };

		if (player) {
			hitActors.AddUnique(player);
			player->reactToHit(pawn, pawn->damage);
		}

	}
	else {
		GEngine->AddOnScreenDebugMessage(511661, 1.0f, FColor::Red, FString("there is no owner pawn"));

	}
}

void AMeleeWeapon::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	TraceForAttack();		
	GEngine->AddOnScreenDebugMessage(11, 1.0f, FColor::Red, FString("meleewaepon overlapped with "));

	;
}
void AMeleeWeapon::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	

	;
}