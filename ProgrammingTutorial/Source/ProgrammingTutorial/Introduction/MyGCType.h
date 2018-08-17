// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyGCType.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMINGTUTORIAL_API UMyGCType : public UObject
{
	GENERATED_BODY()
	
	void CreateDoomedObject()
	{
		UMyGCType* DoomedObject = NewObject<UMyGCType>();
	}
	
	
};
