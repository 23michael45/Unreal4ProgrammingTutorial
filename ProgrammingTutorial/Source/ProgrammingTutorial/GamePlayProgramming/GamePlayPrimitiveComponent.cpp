// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayPrimitiveComponent.h"
#include "GamePlayActor.h"

// Sets default values for this component's properties
UGamePlayPrimitiveComponent::UGamePlayPrimitiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Called every frame
void UGamePlayPrimitiveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{


	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AGamePlayActor* actor = (AGamePlayActor*)GetOwner();

	TickPrint(this, PrimaryComponentTick.TickGroup);
	// ...
}