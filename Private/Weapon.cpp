#include "Weapon.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "HitReactInterface.h"
#include "./shootercpp/PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AWeapon::AWeapon()
{
	//Super();
	PrimaryActorTick.bCanEverTick = true;

	//weaponFront=CreateDefaultSubobject<UBoxComponent>(TEXT("front"));

	//weaponFront->SetupAttachment(itemMesh); //to determine starting location for line trace, i am using this sphere's location
	timeForFiring = 1.0f;  // it is not used because i cancelled autofire
	
	itemMesh->SetNotifyRigidBodyCollision(true);
	itemMesh->BodyInstance.SetCollisionProfileName(FName("BlockAllDynamic"));
	itemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

void AWeapon::BeginPlay()
{
	
	itemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	Super::BeginPlay();
	if (GetOwner())

		GEngine->AddOnScreenDebugMessage(11, 1.0f, FColor::Red, FString(GetOwner()->GetName()));
	//FTimerHandle handle;
	//GetWorldTimerManager().SetTimer(handle, this, &AWeapon::Fire, timeForFiring, true, timeForFiring); // i cancelled this feature to provide player more interactive gameplay 
	// timerForFiring variable is set from weapon datatable
	//setWeaponType("auto");  //initial weapon type
	//sphere->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnComponentBeginOverlap); //bind overlap function to collision / it is actually note sphere it is a box, I named it wrong.
}




void AWeapon::I_Interact(ABaseCharacter* OwnerPawn)
{
	//Super::I_Interact(OwnerPawn);
	EAttachmentRule rule = EAttachmentRule::SnapToTarget;
	FAttachmentTransformRules atRules = FAttachmentTransformRules(rule, true);
	//APlayerCharacter* pawn = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (OwnerPawn) {
		if (!OwnerPawn->activeWeapon==NULL) { OwnerPawn->activeWeapon->Destroy(); };
		GEngine->AddOnScreenDebugMessage(11, 1.0f, FColor::Red, FString("base WeaponClass Attacks"));

		this->SetOwner(OwnerPawn);

		bool AttachmentResult = this->AttachToComponent(OwnerPawn->GetMesh(), atRules, socketName);
		if (AttachmentResult) {
			OwnerPawn->state = ECharacterStates::EEquippedWithMelee;
			//SetActorEnableCollision(1);
			OwnerPawn->activeWeapon = this;
			
			//this->SetActorEnableCollision(0);

		}

	}
}






void AWeapon::Attack() {
	//....
	GEngine->AddOnScreenDebugMessage(11, 1.0f, FColor::Red, FString("base WeaponClass Attacks"));

}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
