// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UCInteractionComponent;
class UAnimMontage;

UCLASS()
class UNREALCOURSE_API ACCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Attack");
	TSubclassOf<AActor> PrimaryProjectile;
	UPROPERTY(EditAnywhere, Category = "Attack");
	TSubclassOf<AActor> BlackholeProjectile;
	UPROPERTY(EditAnywhere, Category = "Attack");
	TSubclassOf<AActor> TeleportProjectile;

	UPROPERTY(EditAnywhere, Category = "Attack");
	UAnimMontage* AttackMontage;

	FTimerHandle Attack_TimerHandler;

	TSubclassOf<AActor> ProjectileToSpawn;


public:
	// Sets default values for this character's properties
	ACCharacter();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCInteractionComponent* InteractionComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void PrimaryInteract();
	void SpawnAbility();

	void AbilityHandler(int ID);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
