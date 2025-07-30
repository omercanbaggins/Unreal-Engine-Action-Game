// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "./shootercpp/overlapInterface.h"
#include "baseObstacle.generated.h"

class USphereComponent;

UCLASS()
class SHOOTERCPP_API AbaseObstacle : public AActor,public IoverlapInterface
{
	GENERATED_BODY()
	
	
public:	
	// Sets default values for this actor's properties
	AbaseObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	float damage = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	UStaticMeshComponent* mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	float lifetime;
	UPROPERTY(EditAnywhere)
	USphereComponent* sphere;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	virtual void Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OverlapReact();
	


};
