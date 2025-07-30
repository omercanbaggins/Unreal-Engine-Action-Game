// Fill out your copyright notice in the Description page of Project Settings.


#include "UCharacterStat.h"
#include "./shootercpp/PlayerCharacter.h"
#include "CharacterStatComponent.h"


void UUCharacterStat::InitializeFromStat(const UUCharacterStat& Stat)
{
	this->baseValue = Stat.baseValue;
	this->statName = Stat.statName;
	this->player = Stat.player;
}

void UUCharacterStat::Initialize(APlayerCharacter* ownerPawn, FName name)

{
	player = ownerPawn;
	statName = name;
	checkStatCompAndAdd(ownerPawn);
}

void UUCharacterStat::Initialize(APlayerCharacter* OwnerPawn, FName Name, float Value)
{
	Initialize(OwnerPawn, Name);
	baseValue = Value;
	currentValue = Value;

}


void UUCharacterStat::checkStatCompAndAdd(APlayerCharacter* ownerPawn) {
	if (ownerPawn) {
		ownerPawn->statComp->AddToStatList(this);
		int numberofStat = ownerPawn->statComp->stats.Num();
		GEngine->AddOnScreenDebugMessage(999, 1.f, FColor::Red, FString::FromInt(numberofStat));
	}
}

void UUCharacterStat::buffDebuff(FAttrBufferInf buffInf)
{
	if (player) {
		bool btActive = player->GetWorldTimerManager().IsTimerActive(timerForBuffOperations);

		if (btActive) player->GetWorldTimerManager().ClearTimer(timerForBuffOperations);

		//currentValue += buffInf.numberToAdd;

		FTimerDelegate delagate; delagate.BindLambda([this, buffInf](){currentValue += buffInf.numberToAdd; });
		player->GetWorldTimerManager().SetTimer(timerForBuffOperations, delagate, buffInf.loopDelay, buffInf.bLoop,0.2f);
	}

}

void UUCharacterStat::increaseStat()
{


	baseValue += 1.f;

}





