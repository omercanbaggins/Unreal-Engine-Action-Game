// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"


class ABaseCharacter;
UCLASS()
class SHOOTERCPP_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void pickUp();


	virtual void I_Interact(ABaseCharacter* OwnerPawn);

	UFUNCTION()
	void overlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	class UWidgetComponent* widget;

	UPROPERTY(EditDefaultsOnly)
	FName itemName;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* itemMesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* rootScene;
	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* sphere;
	/*UPROPERTY(EditDefaultsOnly)

	class UWidgetComponent* widgetComp;
	*/

};
UCLASS()
class SHOOTERCPP_API AMusicTape : public AItem
{
	GENERATED_BODY()

public:

	AMusicTape();
	virtual void I_Interact(ABaseCharacter* OwnerPawn);
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USoundBase* correspondingSound;
	UPROPERTY(EditAnywhere)
	FName musicName;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* musicCover;



};