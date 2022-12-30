// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBaseProjectile.h"
#include "CTeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCOURSE_API ACTeleportProjectile : public ACBaseProjectile
{
	GENERATED_BODY()

public:

	ACTeleportProjectile();

	UPROPERTY(EditDefaultsOnly, Category = "Timers")
	float TimeToExplode;
	UPROPERTY(EditDefaultsOnly, Category = "Timers")
	float TimeToTeleport;
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	UParticleSystem* ExplodeParticle;

	void ExplodeProjectile();
	void TeleportPlayer();

protected:

	FTimerHandle ExplodeHandle;
	FTimerHandle TeleportHandle;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpact, const FHitResult& SweepResult);
};
