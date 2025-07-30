// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "InteractableMusicPlayer.generated.h"

UCLASS()
class SHOOTERCPP_API AInteractableMusicPlayer :public AItem 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableMusicPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void I_Interact(ABaseCharacter* OwnerPawn) override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly)
	class UMusicPlayerComp* mPlayer;
	UPROPERTY(EditDefaultsOnly)
	UAudioComponent* audioComp;

};
