// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sniper.generated.h"

class APlayerCharacter;

UCLASS()
class MEGAJAM_API ASniper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASniper();

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(APlayerCharacter* TargetCharacter);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	APlayerCharacter* Character;
};
