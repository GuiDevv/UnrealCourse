// Fill out your copyright notice in the Description page of Project Settings.


#include "CAttributeComponent.h"

// Sets default values for this component's properties
UCAttributeComponent::UCAttributeComponent()
{
	MaxHealth = 100;
	Health = MaxHealth;
}

bool UCAttributeComponent::ApplyHealthChange(float Delta)
{
	
	Health = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}

bool UCAttributeComponent::GetIsAlive() const
{
	return Health > 0.0;
}

float UCAttributeComponent::GetCurrentHealth() const
{
	return Health;
}

float UCAttributeComponent::GetMaxHealth() const
{
	return MaxHealth;
}

