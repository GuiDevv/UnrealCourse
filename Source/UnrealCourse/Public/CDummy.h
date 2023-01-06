// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDummy.generated.h"

class UCAttributeComponent;

UCLASS()
class UNREALCOURSE_API ACDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UCAttributeComponent* AttributeComponent;

	UFUNCTION()
		void OnHealthChanged(AActor* InstigatorActor, UCAttributeComponent* OwnComponent, float NewHealth, float Delta);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};