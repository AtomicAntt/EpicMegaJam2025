#include "MegaJam/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "MegaJam/Projectile.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	FPSMesh->SetOnlyOwnerSee(true);
	FPSMesh->SetupAttachment(Camera);

	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun"));
	Gun->SetupAttachment(FPSMesh);

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Gun->AttachToComponent(FPSMesh, AttachmentRules, FName(TEXT("GripPoint")));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnCamera", this, &APlayerCharacter::TurnCamera);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::HoldFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::StopFire);
}

void APlayerCharacter::MoveForward(float InputValue) 
{
	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, InputValue);
}

void APlayerCharacter::MoveRight(float InputValue)
{
	FVector RightDirection = GetActorRightVector();
	AddMovementInput(RightDirection, InputValue);
}

void APlayerCharacter::TurnCamera(float InputValue)
{
	AddControllerYawInput(InputValue);
}

void APlayerCharacter::LookUp(float InputValue)
{
	AddControllerPitchInput(InputValue);
}

void APlayerCharacter::Fire()
{
	if (ProjectileClass)
	{
		// Get exact position and direction of the center of the screen, where the crosshair lies.
		APlayerController* PlayerController = Cast<APlayerController>(GetController());

		int32 ViewportSizeX, ViewportSizeY;
		PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
		FVector2D ViewportCenter(ViewportSizeX * 0.5f, ViewportSizeY * 0.5f);

		FVector WorldLocation;
		FVector WorldDirection;

		PlayerController->DeprojectScreenPositionToWorld(ViewportCenter.X, ViewportCenter.Y, WorldLocation,WorldDirection);

		// Calculate exact shooting direction to crosshair using traces (raycasting)
		FVector TraceStart = WorldLocation;
		FVector TraceEnd = TraceStart + (WorldDirection * 10000.0f);

		FHitResult HitResult;
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.AddIgnoredComponent(Gun);
		TraceParams.AddIgnoredComponent(FPSMesh);

		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams);

		FVector TargetPoint;
		if (HitResult.bBlockingHit) 
		{
			TargetPoint = HitResult.ImpactPoint;
		}
		else
		{
			TargetPoint = TraceEnd;
		}
		FVector MuzzleLocation = Gun->GetSocketLocation(TEXT("Fire"));

		FVector ShotDirection = (TargetPoint - MuzzleLocation).GetSafeNormal();
		FRotator MuzzleRotation = ShotDirection.Rotation();

		// Shoot projectile
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				Projectile->FireInDirection(ShotDirection);
			}
		}

		//DrawDebugLine(GetWorld(), TraceStart, TargetPoint, FColor::Red, false, 1.0f, 0, 1.0f);
		//DrawDebugLine(GetWorld(), MuzzleLocation, TargetPoint, FColor::Blue, false, 1.0f, 0, 1.0f);

		// Play animation
		if (FireAnimation != nullptr)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = FPSMesh->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
	}
}

void APlayerCharacter::HoldFire()
{
	GetWorldTimerManager().ClearTimer(FireTimerHandle);
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &APlayerCharacter::Fire, FireDelay, true);

	// This is for the first shot
	Fire();
}

void APlayerCharacter::StopFire()
{
	GetWorldTimerManager().ClearTimer(FireTimerHandle);
}
