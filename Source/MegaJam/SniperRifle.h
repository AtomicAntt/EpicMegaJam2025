// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SniperRifle.generated.h"

class APlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEGAJAM_API ASniperRifle : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ASniperRifle();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachWeapon(APlayerCharacter* TargetCharacter);

private:
	APlayerCharacter* Character;
		
};
