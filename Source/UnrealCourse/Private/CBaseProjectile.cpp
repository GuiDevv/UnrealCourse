// Fill out your copyright notice in the Description page of Project Settings.


#include "CBaseProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ACBaseProjectile::ACBaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	RootComponent = SphereComponent;
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComponent");
	ParticleSystemComponent->SetupAttachment(SphereComponent);
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");

	SphereComponent->SetCollisionProfileName("Projectile");

	MovementComponent->InitialSpeed = 1000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bInitialVelocityInLocalSpace = true;

	InitialLifeSpan = 2.0f;
}

// Called when the game starts or when spawned
void ACBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}

// Called every frame
void ACBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

