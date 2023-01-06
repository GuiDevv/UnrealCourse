// Fill out your copyright notice in the Description page of Project Settings.


#include "CExplosiveBarrel.h"

#include "CAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleEmitter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ACExplosiveBarrel::ACExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("Force Component");
	ForceComp->SetupAttachment(StaticComp);

	ForceComp->SetAutoActivate(false);
	ForceComp->Radius = 750.0f;
	ForceComp->ForceStrength = 2500.0f;
	ForceComp->bImpulseVelChange = true;
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);

	StaticComp->SetCollisionObjectType(ECC_Destructible);
}

// Called when the game starts or when spawned
void ACExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StaticComp->OnComponentHit.AddDynamic(this, &ACExplosiveBarrel::OnActorHit);

}

void ACExplosiveBarrel::OnActorHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpact, const FHitResult& SweepResult)
{
	FVector ExplosionLocation = GetActorLocation() + FVector(0, 0, 70);
	FTransform ExplosionTransform = FTransform(GetActorRotation(), ExplosionLocation, FVector(2, 2, 2));

	UParticleSystemComponent* MyParticles = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, ExplosionTransform);

	ForceComp->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("On Actor Hit in Explosive Barrel"));
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString StringMessage = FString::Printf(TEXT("Hit at Location: %s"), *SweepResult.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), SweepResult.ImpactPoint, StringMessage, nullptr, FColor::Green, 2.0f, true);

	if (OtherActor)
	{
		UCAttributeComponent* Attribute = Cast<UCAttributeComponent>(OtherActor->GetComponentByClass(UCAttributeComponent::StaticClass()));
		if (Attribute)
			Attribute->ApplyHealthChange(-50);
	}	

	Destroy();
}

// Called every frame
void ACExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

