// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicPlayerComp.h"
#include "./Components/AudioComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
UMusicPlayerComp::UMusicPlayerComp()
{
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UMusicPlayerComp::BeginPlay()
{
	Super::BeginPlay();
	

	
}

void UMusicPlayerComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMusicPlayerComp::setSound() {
	AUcomponent->SetSound(updateMusic());
	AUcomponent->Activate();
	MusicStartIndex++;
}
UAudioComponent* UMusicPlayerComp::GetAudioComponent(UAudioComponent* audioComp) {
	
	return audioComp;
}

USoundBase* UMusicPlayerComp::updateMusic()
{
	int numberofSound = soundList.Num();
	if (numberofSound != 0) {
		if (MusicStartIndex <= numberofSound - 1) {
			return soundList[MusicStartIndex];

		}
		else {
			MusicStartIndex = 0;
			return soundList[MusicStartIndex];

		}

	}
	else {
		return NULL;
	}

	
}
	
void UMusicPlayerComp::bindAudioComponent(UAudioComponent* comp) {  //binds a method to audio component passed from bp side. 
	// method which was binded will be invoked when music ended.
	AUcomponent = comp;
	if (AUcomponent && !AUcomponent->OnAudioFinished.IsBound()) {
		setSound();
		AUcomponent->OnAudioFinished.AddDynamic(this, &UMusicPlayerComp::setSound);

	}

}