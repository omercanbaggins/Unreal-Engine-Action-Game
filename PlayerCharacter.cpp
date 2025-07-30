// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "overlapInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Debug/DebugDrawComponent.h"
#include "Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "./Public/UCharacterStat.h"
#include "CharacterStatComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	statComp = CreateDefaultSubobject<UCharacterStatComponent>(FName("statWrapper"));
	
	
	

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//UCapsuleComponent* capsule 
	GetCharacterMovement()->JumpZVelocity = 600;
	JumpMaxCount = 2;
 	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::overlap);

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Move(1.f);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("interact", IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction("fire", IE_Pressed, this, &APlayerCharacter::performAttack);
	PlayerInputComponent->BindAction("fire", IE_Released, this, &APlayerCharacter::pauseFire);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("right", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("lookUp", this, &APlayerCharacter::lookUp);
	PlayerInputComponent->BindAxis("lookArround", this, &APlayerCharacter::lookRight);

	PlayerInputComponent->BindAxis("move", this, &APlayerCharacter::Move);

}
void APlayerCharacter::lookRight(float Value) {
	AddControllerYawInput(Value);
	//GEngine->AddOnScreenDebugMessage(54, 1.f, FColor::Red, FString::SanitizeFloat(Value));

}
void APlayerCharacter::lookUp(float Value) {
	AddControllerPitchInput(Value);
	//GEngine->AddOnScreenDebugMessage(53, 1.f, FColor::Red, FString::SanitizeFloat(Value));

}
void APlayerCharacter::MoveRight(float Value) {
	double Yaw = GetControlRotation().Yaw;
	FRotator YawRotation = FRotator(0, Yaw,0);
	FVector rightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	if (!bKilled) AddMovementInput(rightVector * Value, 1);
}

void APlayerCharacter::Move(float Value) {
	double Yaw = GetControlRotation().Yaw;
	FRotator YawRotation = FRotator(0, Yaw, 0);
	FVector forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	if(!bKilled) AddMovementInput(forward, Value);
}
void APlayerCharacter::overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	IoverlapInterface* overlappedActor = Cast<IoverlapInterface>(OtherActor);
	if (overlappedActor) {
		overlappedActor->OverlapReact();
	}
}
void APlayerCharacter::Attack() {
	;
}
void APlayerCharacter::Interact() {

	FVector start = GetActorLocation() + 200 * GetActorForwardVector();
	FHitResult hr;
	FVector end = start + 100 * GetActorForwardVector();
	TArray<AActor*>actors;
	actors.Add(this);
	UKismetSystemLibrary::SphereTraceSingle(this, start, start + 1000 *GetActorForwardVector(),
		64, ETraceTypeQuery::TraceTypeQuery1,false, actors,EDrawDebugTrace::None,hr,true);
	DrawDebugSphere(GetWorld(), start, 64, 1, FColor::Blue, false, 9.f);
	DrawDebugSphere(GetWorld(), end, 64, 2, FColor::Blue, false, 9.f);
	AItem* item = Cast<AItem>(hr.GetActor());
	if (item) {
		item->I_Interact(this);
	}
	else {
		//GEngine->AddOnScreenDebugMessage(55, 1.f, FColor::Red, FString("there is no hit or hit actor is not interactable"));
	}

}
/*if (hr.bBlockingHit) {
		EAttachmentRule rule = EAttachmentRule::SnapToTarget;
		FAttachmentTransformRules atRules = FAttachmentTransformRules(rule, true);
		weapon = Cast<AWeapon>(hr.GetActor());
		bool b=0;
		if (weapon) b= hr.GetActor()->AttachToComponent(GetMesh(), atRules, FName("hand"));
		if (b)
		{
			state = ECharacterStates::EEquipped;
			hr.GetActor()->SetActorEnableCollision(0);
		}
	
	}*/

void APlayerCharacter::performAttack() {
	if (activeWeapon) {
		//GEngine->AddOnScreenDebugMessage(55, 1.f, FColor::Red, FString("attacked"));

		FTimerDelegate timerDelagate = FTimerDelegate::CreateLambda([this]()->void {activeWeapon->Attack(); });
		GetWorldTimerManager().SetTimer(weaponTimerH, timerDelagate, 0.1f, true);
		activeWeapon->Attack();
		float speedAvantage = 0;


		if (statComp&& statComp->returnSpecificStat(EStatNames::agility)) {

			speedAvantage = statComp->returnSpecificStat(EStatNames::agility)->getBaseValue()/10;

		}
		calculateDamage();
		int rand = UKismetMathLibrary::RandomIntegerInRange(1, 3);
		FString str = FString(FName("Attack").ToString()) + FString::FromInt(rand);
		GetMesh()->GetAnimInstance()->Montage_Play(activeWeapon->animToPlay, 1.f+ speedAvantage);
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName(str), activeWeapon->animToPlay);


		//weapon->animToPlay;
		//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString("fired"), true);

	}
	else {
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString("failed"), true);

	}
}
void APlayerCharacter::pauseFire() {
	GetWorldTimerManager().ClearTimer(weaponTimerH);

}

void APlayerCharacter::useItem() {
	int arraySize = inventory.Num();
	if(!(arraySize==0)){
		int rand = UKismetMathLibrary::RandomInteger(arraySize);
		inventory[rand]->I_Interact(this);
	}
	else
	GEngine->AddOnScreenDebugMessage(123, 1.f, FColor::Red, FString("array is empty"));
}

void APlayerCharacter::addToHealth(float v) {


	float endAvantage = statComp->returnSpecificStat(EStatNames::endurance)->getBaseValue();
	v -= v * endAvantage / 10;
	GEngine->AddOnScreenDebugMessage(12113, 1.f, FColor::Red, FString::FromInt(v));

	health -= v;
	Die();
}

void APlayerCharacter::calculateDamage()
{
	float strAdvatage = statComp->returnSpecificStat(EStatNames::strenght)->getBaseValue();
	damage = damage + strAdvatage /2.f;

}

/*
void EStatNames::getValueOfStat(EStatNames stat) {
	returnSpecificStat(EStatNames::endurance)->getBaseValue();

}
*/





/*
void APlayerCharacter::Jump() {
	;
}*/