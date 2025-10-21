// Fill out your copyright notice in the Description page of Project Settings.


#include "SniperRifle.h"
#include "MegaJam/Player/PlayerCharacter.h"
#include "Engine/World.h"

// Sets default values for this component's properties
ASniperRifle::ASniperRifle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;
	// ...
}

void ASniperRifle::AttachWeapon(APlayerCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	GetRootComponent()->AttachToComponent(Character->GetFPSMesh(), AttachmentRules, FName(TEXT("GripPoint")));
	//RegisterComponent();

	//Character->AddInstanceComponent(this);
}

