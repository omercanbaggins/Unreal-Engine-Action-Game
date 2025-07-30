// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "./shootercpp/PlayerCharacter.h"
#include "BaseCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
//#include "Components/WidgetComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	rootScene = CreateDefaultSubobject<USceneComponent>(FName("root"));
	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("mesh"));
	sphere = CreateDefaultSubobject<UBoxComponent>(FName("col"));
	SetRootComponent(rootScene);
	sphere->SetupAttachment(RootComponent);
	itemMesh->SetupAttachment(sphere);
	//widgetComp = CreateDefaultSubobject<UWidgetComponent>(FName("widget"));
	//widgetComp->SetupAttachment(itemMesh);
	//widget = CreateDefaultSubobject<UWidgetComponent>(FName("widget"));

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	//widget->SetVisibility(0);
	sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::overlap);
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::pickUp()
{
	APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0);
	APawn* pawn = controller->GetPawn();
	APlayerCharacter* player = Cast<APlayerCharacter>(pawn);
	if (player) {
		SetOwner(player);
		player->inventory.Add(this);
		Destroy();
		
	}
	
}

void AItem::I_Interact(ABaseCharacter* OwnerPawn)
{
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, FString(GetName()));

}
void AItem::overlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult){
	//widgetComp->InitializeComponent();
	//widgetComp->SetVisibility(1);

}

AMusicTape::AMusicTape()
{
	;
}

void AMusicTape::I_Interact(ABaseCharacter* OwnerPawn)
{
	if (OwnerPawn) {
		OwnerPawn->musicList.Add(this);
		
		;
	}
}
