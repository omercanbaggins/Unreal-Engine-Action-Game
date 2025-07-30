// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatComponent.h"
#include "./shootercpp/Public/UCharacterStat.h"
#include "./shootercpp/PlayerCharacter.h"
// Sets default values for this component's properties
UCharacterStatComponent::UCharacterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<APlayerCharacter>(GetOwner());

	if(player){
		enduranceStat = NewObject<UUCharacterStat>();
		strenghtStat = NewObject<UUCharacterStat>();
		agilityStat = NewObject<UUCharacterStat>();
		intelligenceStat = NewObject<UUCharacterStat>();

		enduranceStat->Initialize(player,"endurance", 1.f);
		strenghtStat->Initialize(player, "strenght", 1.f);
		agilityStat->Initialize(player, "agility", 1.f);
		intelligenceStat->Initialize(player, "intelligence", 1.f);

	}
	
}

void UCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

UUCharacterStat* UCharacterStatComponent::returnSpecificStat(EStatNames statName) {
	switch (statName)
	{
	case EStatNames::endurance:
		return enduranceStat;
	case EStatNames::agility:
		return agilityStat;
		break;
	case EStatNames::strenght:
		return strenghtStat;
		break;
	case EStatNames::intelligence:
		return intelligenceStat;
		break;
	default:
		return NULL;
		break;
	}


}

void UCharacterStatComponent::AddToStatList(UUCharacterStat* stat) {
	if (stat) {
		stats.AddUnique(stat);
	}
	
	;
}

UUCharacterStat* UCharacterStatComponent::getStatFromList(FName name) {

	for (UUCharacterStat* stat : stats) {
		if (stat->getStatName() == name) {
			return stat;
		};
	}
	return NULL;
}