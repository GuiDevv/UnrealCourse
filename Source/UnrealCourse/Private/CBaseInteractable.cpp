// Fill out your copyright notice in the Description page of Project Settings.


#include "CBaseInteractable.h"

// Sets default values
ACBaseInteractable::ACBaseInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;

}

// Called when the game starts or when spawned
void ACBaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACBaseInteractable::Interact_Implementation(APawn* InstigatorPawn)
{
	
}

// Called every frame
void ACBaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

