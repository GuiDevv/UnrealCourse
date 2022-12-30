// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBaseProjectile.h"
#include "GameFramework/Actor.h"
#include "CMagicProjectile.generated.h"

UCLASS()
class UNREALCOURSE_API ACMagicProjectile : public ACBaseProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACMagicProjectile();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
