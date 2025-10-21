// Fill out your copyright notice in the Description page of Project Settings.


#include "Sniper.h"
#include "MegaJam/Player/PlayerCharacter.h"

// Sets default values
ASniper::ASniper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASniper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASniper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASniper::AttachWeapon(APlayerCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetFPSMesh(), AttachmentRules, FName(TEXT("GripPoint")));

	//Character->AddInstanceComponent(this);
}

