// Fill out your copyright notice in the Description page of Project Settings.


#include "CDummy.h"

#include "CAttributeComponent.h"

// Sets default values
ACDummy::ACDummy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMeshComponent;
	AttributeComponent = CreateDefaultSubobject<UCAttributeComponent>("AttributeComponent");
	AttributeComponent->OnHealthChanged.AddDynamic(this, &ACDummy::OnHealthChanged);
}

// Called when the game starts or when spawned
void ACDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACDummy::OnHealthChanged(AActor* InstigatorActor, UCAttributeComponent* OwnComponent, float NewHealth, float Delta)
{
	if (Delta < 0)
		StaticMeshComponent->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
}

// Called every frame
void ACDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

