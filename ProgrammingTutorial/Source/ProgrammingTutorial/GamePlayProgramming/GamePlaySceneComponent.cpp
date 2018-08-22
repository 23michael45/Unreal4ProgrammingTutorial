// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlaySceneComponent.h"

#include "GamePlayActor.h"

// Sets default values for this component's properties
UGamePlaySceneComponent::UGamePlaySceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGamePlaySceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGamePlaySceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AGamePlayActor* actor = (AGamePlayActor*)GetOwner();


	TickPrint(this, PrimaryComponentTick.TickGroup);
	// ...
}

