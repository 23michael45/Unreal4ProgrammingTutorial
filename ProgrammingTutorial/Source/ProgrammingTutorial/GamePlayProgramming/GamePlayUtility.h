// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
/**
 * 
 */
class PROGRAMMINGTUTORIAL_API GamePlayUtility
{
public:
	GamePlayUtility();
	~GamePlayUtility();


public: 
	void TickPrint(UObject* obj, enum ETickingGroup tick);
};
