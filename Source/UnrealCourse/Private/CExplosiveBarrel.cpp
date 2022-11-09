// Fill out your copyright notice in the Description page of Project Settings.


#include "CExplosiveBarrel.h"

#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ACExplosiveBarrel::ACExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticComp->OnComponentBeginOverlap.AddDynamic(this, &ACExplosiveBarrel::OnOverlapBegin);

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("ExplosionParticle");
	EffectComp->SetupAttachment(StaticComp);

}

// Called when the game starts or when spawned
void ACExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACExplosiveBarrel::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();
}

// Called every frame
void ACExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

