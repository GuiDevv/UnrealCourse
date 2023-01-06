// Fill out your copyright notice in the Description page of Project Settings.


#include "CMagicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "CAttributeComponent.h"

// Sets default values
ACMagicProjectile::ACMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	if (OtherActor && OtherActor != GetInstigator())
	{
		UCAttributeComponent* Attibute = Cast<UCAttributeComponent>(OtherActor->GetComponentByClass(UCAttributeComponent::StaticClass()));

		if (Attibute)
		{
			Attibute->ApplyHealthChange(Damage);
		}
	}

	Super::OnActorOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

// Called every frame
void ACMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

