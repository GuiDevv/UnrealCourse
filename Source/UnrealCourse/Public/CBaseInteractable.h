// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "CBaseInteractable.generated.h"

UCLASS()
class UNREALCOURSE_API ACBaseInteractable : public AActor, public ICGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBaseInteractable();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Interact_Implementation(APawn* InstigatorPawn) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
