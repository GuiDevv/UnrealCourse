// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "CChest.generated.h"

UCLASS()
class UNREALCOURSE_API ACChest : public AActor, public ICGameplayInterface
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ACChest();

	UPROPERTY(EditAnywhere)
	float TargetPitch;

	void Interact_Implementation(APawn* InstigatorPawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
