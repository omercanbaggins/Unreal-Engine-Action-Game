// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UCharacterStat.generated.h"


class APlayerCharacter;

USTRUCT(BlueprintType)
struct SHOOTERCPP_API FAttrBufferInf {
	GENERATED_BODY()
public:
	FAttrBufferInf():bLoop(false), numberToAdd(0.f), willItBeReset(false), loopDelay(0.f){}

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bLoop;//set true if you want to give buff/debuff continueously
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float numberToAdd; //this number will be add up to currentvalue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool willItBeReset;	//after timer finished, if you want to make current value equal to old current value, set true
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float loopDelay;
};

UCLASS(Blueprintable)
class SHOOTERCPP_API UUCharacterStat : public UObject
{
	GENERATED_BODY()
public:
	UUCharacterStat() : baseValue(0.0f), currentValue(0.0f), player(nullptr), statName(NAME_None) {};
	void InitializeFromStat(const UUCharacterStat& Stat);
	void Initialize(APlayerCharacter* OwnerPawn, FName Name);
	void Initialize(APlayerCharacter* OwnerPawn, FName Name, float Value);

	void checkStatCompAndAdd(APlayerCharacter* ownerPawn);

	UFUNCTION(BlueprintCallable)
	void buffDebuff(FAttrBufferInf buffInf);// applies temporal effect;
	UFUNCTION(BlueprintCallable)
	void increaseStat();	// permanently increases value of stat;
	
	UFUNCTION(BlueprintCallable)
	float getCurrentValue() const {return currentValue;};
	UFUNCTION(BlueprintCallable)
	float getExactValue() const {return baseValue;};
	UFUNCTION(BlueprintCallable)
	FName getStatName() const {return statName;}
	UFUNCTION(BlueprintCallable)
	void resetCurrentValue() {currentValue = baseValue;}
	UFUNCTION(BlueprintCallable)
	void setOwnerPlayer(APlayerCharacter* playerp) {
		player=playerp;
	}	
	UFUNCTION(BlueprintCallable)
	void setBaseValue(float v) {
		baseValue = v;
	}
	UFUNCTION(BlueprintCallable)
	float getBaseValue() const {
		return baseValue;
	}
	
	
private:
	FTimerHandle timerForBuffOperations;
	UPROPERTY(EditAnywhere)
	float baseValue = 1.f;
	UPROPERTY(EditAnywhere)
	float currentValue = 1.f;
	UPROPERTY(EditAnywhere)
	FName statName;
	APlayerCharacter* player;



};
