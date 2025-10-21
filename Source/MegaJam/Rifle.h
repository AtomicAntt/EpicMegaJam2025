// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Rifle.generated.h"

/**
 * 
 */

class APlayerCharacter;

UCLASS()
class MEGAJAM_API URifle : public USkeletalMeshComponent
{
	GENERATED_BODY()
private:
	APlayerCharacter* Character;
};
