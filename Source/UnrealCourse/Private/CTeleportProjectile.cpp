// Fill out your copyright notice in the Description page of Project Settings.


#include "CTeleportProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ACTeleportProjectile::ACTeleportProjectile()
{
	TimeToExplode = 0.2f;
	TimeToTeleport = 0.2f;
	InitialLifeSpan = 1.0f;
}

void ACTeleportProjectile::ExplodeProjectile()
{
	MovementComponent->StopMovementImmediately();

	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ACTeleportProjectile::TeleportPlayer, TimeToTeleport, false);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeParticle, GetActorLocation(), FRotator::ZeroRotator);
}

void ACTeleportProjectile::TeleportPlayer()
{
	AActor* TargetToTeleport = GetInstigator();

	if(TargetToTeleport)
		TargetToTeleport->TeleportTo(GetActorLocation(), TargetToTeleport->GetActorRotation(), false, false);
}

void ACTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	
	GetWorldTimerManager().SetTimer(ExplodeHandle, this, &ACTeleportProjectile::ExplodeProjectile, TimeToExplode, false);

	SphereComponent->OnComponentHit.AddDynamic(this, &ACTeleportProjectile::OnActorHit);
}

void ACTeleportProjectile::OnActorHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpact, const FHitResult& SweepResult)
{
	if (GetWorldTimerManager().IsTimerActive(ExplodeHandle))
		GetWorldTimerManager().ClearTimer(ExplodeHandle);
	if(GetWorldTimerManager().IsTimerActive(TeleportHandle))
		GetWorldTimerManager().ClearTimer(TeleportHandle);

	TeleportPlayer();
}

void ACTeleportProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ACTeleportProjectile::OnProjectileOverlap_Implementation()
{
	Super::OnProjectileOverlap_Implementation();
}
