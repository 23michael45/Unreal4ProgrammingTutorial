// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GamePlayActorComponent.h"
#include "GamePlaySceneComponent.h"
#include "GamePlayPrimitiveComponent.h"
#include "GamePlayUtility.h"
#include "GamePlayActor.generated.h"

UCLASS()
class PROGRAMMINGTUTORIAL_API AGamePlayActor : public AActor, public GamePlayUtility
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGamePlayActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = Component)
		UGamePlayActorComponent* actorComponent;
	UPROPERTY(VisibleAnywhere, Category = Component)
		UGamePlaySceneComponent* sceneComponent;
	UPROPERTY(VisibleAnywhere, Category = Component)
		UGamePlayPrimitiveComponent* primitiveComponent;
	UPROPERTY(VisibleAnywhere, Category = Component)
		UGamePlayPrimitiveComponent* primitiveComponent2;

	UPROPERTY(EditAnywhere, Category = Component)
		TEnumAsByte<ETickingGroup> tickgroupActor;

	int tickCount = 0;
};
