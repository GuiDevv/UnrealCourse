// Fill out your copyright notice in the Description page of Project Settings.


#include "CBaseProjectile.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
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
	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	AudioComponent->SetupAttachment(SphereComponent);

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
	if (AudioComponent)
	{
		AudioComponent->Sound = LoopSound;
		AudioComponent->Play();
	}
		
}

void ACBaseProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ACBaseProjectile::OnActorOverlap);
}

void ACBaseProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnProjectileOverlap();
}

void ACBaseProjectile::OnProjectileOverlap_Implementation()
{
	if((!IsPendingKill()))
	{
		if(ImpactVFX)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactVFX, GetActorLocation(), GetActorRotation());
		if (ImpactSound)
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		if (AudioComponent)
			AudioComponent->Stop();
		Destroy();
	}
}

// Called every frame
void ACBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

