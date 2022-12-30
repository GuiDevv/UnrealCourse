// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CExplosiveBarrel.generated.h"

class URadialForceComponent;

UCLASS()
class UNREALCOURSE_API ACExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACExplosiveBarrel();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UStaticMeshComponent* StaticComp;
	UPROPERTY(VisibleAnywhere);
	URadialForceComponent* ForceComp;
	UPROPERTY(EditDefaultsOnly, Category="VFX")
	UParticleSystem* ExplosionEffect;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	//Must be marked with UFUNCTION in order to 'bind' the event
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpact, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
