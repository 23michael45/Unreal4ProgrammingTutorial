// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "GamePlayUtility.h"
#include "GamePlayPrimitiveComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMINGTUTORIAL_API UGamePlayPrimitiveComponent : public UPrimitiveComponent,public GamePlayUtility
{
	GENERATED_BODY()
	
	
public:
	UGamePlayPrimitiveComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	
};
