// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableMusicPlayer.h"
#include "MusicPlayerComp.h"
#include "Components/AudioComponent.h"
// Sets default values
AInteractableMusicPlayer::AInteractableMusicPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mPlayer = CreateDefaultSubobject<UMusicPlayerComp>(FName("musicplayer"));
	audioComp = CreateDefaultSubobject<UAudioComponent>(FName("audioComp"));
	//mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("staticMesh"));
	SetRootComponent(mesh);
	audioComp->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AInteractableMusicPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableMusicPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableMusicPlayer::I_Interact(ABaseCharacter* OwnerPawn)
{
	if (mPlayer) {
		mPlayer->bindAudioComponent(audioComp);
	}
}

