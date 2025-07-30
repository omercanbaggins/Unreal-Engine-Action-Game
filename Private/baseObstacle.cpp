// Fill out your copyright notice in the Description page of Project Settings.


#include "baseObstacle.h"
#include "./shootercpp/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "./Components/SphereComponent.h"

AbaseObstacle::AbaseObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("mesh"));
	sphere = CreateDefaultSubobject<USphereComponent>(FName("sphere"));
	SetRootComponent(mesh);
	sphere->SetupAttachment(mesh);
	SetLifeSpan(lifetime);
}

// Called when the game starts or when spawned
void AbaseObstacle::BeginPlay()
{
	Super::BeginPlay();
	sphere->OnComponentBeginOverlap.AddDynamic(this, &AbaseObstacle::Overlap);

}

// Called every frame
void AbaseObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

 void AbaseObstacle::Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
	APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
	if (player) { //player->addToHealth(damage);
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, player->GetName()); }

}
void AbaseObstacle::OverlapReact()
{
	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
	if (player) { player->addToHealth(damage); GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, player->GetName()); }
	else {GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Red, FString("nopalyer"));}
}

