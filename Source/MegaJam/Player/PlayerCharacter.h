#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class MEGAJAM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void StopFire();

	UFUNCTION()
	void HoldFire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	USkeletalMeshComponent* GetFPSMesh() const { return FPSMesh; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float FireDelay = 0.27f;

protected:

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* FPSMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Gun;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	void MoveForward(float InputValue);
	void MoveRight(float InputValue);
	void TurnCamera(float InputValue);
	void LookUp(float InputValue);
	
private:
	FTimerHandle FireTimerHandle;
};
