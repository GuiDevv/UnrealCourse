// Fill out your copyright notice in the Description page of Project Settings.


#include "CMagicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ACMagicProjectile::ACMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComponent");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 1.0f;

}

// Called when the game starts or when spawned
void ACMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

