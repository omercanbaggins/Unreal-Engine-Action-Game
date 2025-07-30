// Fill out your copyright notice in the Description page of Project Settings.


#include "MysteryBox.h"
#include "./shootercpp/PlayerCharacter.h"
#include "./shootercpp/public/UCharacterStat.h"
#include "./shootercpp/Public/CharacterStatComponent.h"
AMysteryBox::AMysteryBox()
{
	stat = EStats::strength;
}

void AMysteryBox::Open(APlayerCharacter* player)
{
	if (player && player->statComp) {
		player->statComp->returnSpecificStat(EStatNames::agility);
	}
	

}

void AMysteryBox::CheckReq(UUCharacterStat* statToControl) {
	bool bValueEnough = this->StatValueReq <= statToControl->getCurrentValue();
	bValueEnough ? GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, FString("box been opened")) : GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, FString("box hasn't been opened"));

}

