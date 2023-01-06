// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBaseInteractable.h"
#include "CHealingPotion.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCOURSE_API ACHealingPotion : public ACBaseInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACHealingPotion();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	float HealthFactor;

	bool isActive = true;

	void Interact_Implementation(APawn* InstigatorPawn) override;
	void ResetPotion();
	
};
