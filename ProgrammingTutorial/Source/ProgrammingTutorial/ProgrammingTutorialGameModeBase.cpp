// Fill out your copyright notice in the Description page of Project Settings.

#include "ProgrammingTutorialGameModeBase.h"





void AProgrammingTutorialGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		// Display a debug message for five seconds. 
		// The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Run AProgrammingTutorialGameModeBase!"));
	}
}
