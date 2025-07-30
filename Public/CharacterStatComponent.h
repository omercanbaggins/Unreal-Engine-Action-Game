// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatComponent.generated.h"

class UUCharacterStat;
UENUM(Blueprintable)
enum class EStatNames :uint8 {
	endurance,
	agility,
	strenght,
	intelligence
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERCPP_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	UUCharacterStat* returnSpecificStat(EStatNames statName);

	void AddToStatList(UUCharacterStat* stat);

	UFUNCTION(BlueprintCallable)
	UUCharacterStat* getStatFromList(FName name);

	UPROPERTY(BlueprintReadOnly)
	TArray<UUCharacterStat*> stats;



	class APlayerCharacter* player;
private:

	UUCharacterStat* enduranceStat;
	UUCharacterStat* agilityStat;
	UUCharacterStat* strenghtStat;
	UUCharacterStat* intelligenceStat;
		
};
