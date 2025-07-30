// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "baseObstacle.h"
#include "MysteryBox.generated.h"

class UUCharacterStat;
class APlayerCharacter;
/**
 * 
 */

UENUM()
enum class EStats :uint8 {
	strength=1,
	agility,
	endurance
};

UCLASS()
class SHOOTERCPP_API AMysteryBox : public AbaseObstacle
{
	GENERATED_BODY()
public:
	AMysteryBox();
	UPROPERTY(EditAnywhere)
	float StatValueReq;
	UPROPERTY(EditAnywhere)
	FName StatNameToOpen;
	UPROPERTY(EditAnywhere)
	EStats stat = EStats::strength;
	UFUNCTION(BlueprintCallable)
	void Open(APlayerCharacter* player);
	UFUNCTION(BlueprintCallable)
	void CheckReq(UUCharacterStat* statToControl);
	

};
