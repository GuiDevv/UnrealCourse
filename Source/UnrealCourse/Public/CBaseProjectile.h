// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class UNREALCOURSE_API ACBaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBaseProjectile();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* MovementComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* ParticleSystemComponent;
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	UParticleSystem* ImpactVFX;
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* LoopSound;
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* ImpactSound;
	UAudioComponent* AudioComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnProjectileOverlap();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
