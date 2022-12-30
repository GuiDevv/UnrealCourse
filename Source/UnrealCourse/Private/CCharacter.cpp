// Fill out your copyright notice in the Description page of Project Settings.


#include "CCharacter.h"

#include "CInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CInteractionComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACCharacter::ACCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);
	InteractionComp = CreateDefaultSubobject<UCInteractionComponent>("InteractionComponent");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACCharacter::MoveForward(float Value)
{
	FRotator ControllerRot = GetControlRotation();
	ControllerRot.Pitch = 0.0f;
	ControllerRot.Roll = 0.0f;

	AddMovementInput(ControllerRot.Vector(), Value);
}

void ACCharacter::MoveRight(float Value)
{
	FRotator ControllerRot = GetControlRotation();
	ControllerRot.Pitch = 0.0f;
	ControllerRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControllerRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void ACCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

void ACCharacter::SpawnAbility()
{
	if (ensureAlways(ProjectileToSpawn))
	{
		FRotator ProjectileRotation;
		float Distance = 2500.0f;
		FVector Start, End;
		FHitResult Hit;
		FCollisionQueryParams QueryParams;

		QueryParams.AddIgnoredActor(this);
		Start = CameraComp->GetComponentLocation();
		End = (CameraComp->GetForwardVector() * Distance) + CameraComp->GetComponentLocation();

		GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Camera, QueryParams);

		if (Hit.bBlockingHit)
			ProjectileRotation = UKismetMathLibrary::FindLookAtRotation(GetMesh()->GetSocketLocation("Muzzle_01"), Hit.ImpactPoint);
		else
			ProjectileRotation = UKismetMathLibrary::FindLookAtRotation(GetMesh()->GetSocketLocation("Muzzle_01"), Hit.TraceEnd);


		FTransform SpawnTM = FTransform(ProjectileRotation, GetMesh()->GetSocketLocation("Muzzle_01"));
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Instigator = this;

		GetWorld()->SpawnActor<AActor>(ProjectileToSpawn, SpawnTM, SpawnParameters);
	}	
}

void ACCharacter::AbilityHandler(int ID)
{
	PlayAnimMontage(AttackMontage);

	switch (ID)
	{
	case 0: ProjectileToSpawn = PrimaryProjectile;
		break;
	case 1: ProjectileToSpawn = BlackholeProjectile;
		break;
	case 2: ProjectileToSpawn = TeleportProjectile;
		break;
	}

	GetWorldTimerManager().SetTimer(Attack_TimerHandler, this, &ACCharacter::SpawnAbility, 0.2);
}

// Called every frame
void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ACCharacter::PrimaryInteract);

	DECLARE_DELEGATE_OneParam(FCustomInputDelegate, const int)
	PlayerInputComponent->BindAction<FCustomInputDelegate>("PrimaryAttack", IE_Pressed, this, &ACCharacter::AbilityHandler, 0);
	DECLARE_DELEGATE_OneParam(FCustomInputDelegate, const int)
	PlayerInputComponent->BindAction<FCustomInputDelegate>("BlackholeAbility", IE_Pressed, this, &ACCharacter::AbilityHandler, 1);
	DECLARE_DELEGATE_OneParam(FCustomInputDelegate, const int)
	PlayerInputComponent->BindAction<FCustomInputDelegate>("TeleportAbility", IE_Pressed, this, &ACCharacter::AbilityHandler, 2);

}

