// Fill out your copyright notice in the Description page of Project Settings.


#include "CInteractionComponent.h"
#include <CGameplayInterface.h>

// Sets default values for this component's properties
UCInteractionComponent::UCInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UCInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCInteractionComponent::PrimaryInteract()
{
	AActor* MyOwner = GetOwner();

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector EyeLocation;
	FRotator EyeRotator;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotator);

	FVector End = EyeLocation  + (EyeRotator.Vector() * 1000);

	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	Shape.SetSphere(30.0f);

	GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();

		if (HitActor)
		{
			if (HitActor->Implements<UCGameplayInterface>())
			{
				APawn* Pawn = Cast<APawn>(MyOwner);
				ICGameplayInterface::Execute_Interact(HitActor, Pawn);
				break;
			}
		}

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 30.0f, 32, FColor::Red, false, 1.0f, 0, 2.0f);
	}

}
