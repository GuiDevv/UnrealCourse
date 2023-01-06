// Fill out your copyright notice in the Description page of Project Settings.


#include "CHealingPotion.h"

#include "CAttributeComponent.h"

ACHealingPotion::ACHealingPotion()
{
	HealthFactor = 50.0f;
}

void ACHealingPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (InstigatorPawn && isActive)
	{
		UCAttributeComponent* AttributeComponent = Cast<UCAttributeComponent>(InstigatorPawn->GetComponentByClass(UCAttributeComponent::StaticClass()));
		if (AttributeComponent)
			if(AttributeComponent->GetCurrentHealth() < AttributeComponent->GetMaxHealth())
			{
				isActive = false;
				AttributeComponent->ApplyHealthChange(HealthFactor);
				MeshComponent->SetVisibility(false);
				MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				FTimerHandle ResetTimer;
				GetWorldTimerManager().SetTimer(ResetTimer, this, &ACHealingPotion::ResetPotion, 10.0f);
			}
				
	}	
}

void ACHealingPotion::ResetPotion()
{
	isActive = true;
	MeshComponent->SetVisibility(true);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
