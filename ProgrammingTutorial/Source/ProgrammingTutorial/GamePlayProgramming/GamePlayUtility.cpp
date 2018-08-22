// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayUtility.h"

GamePlayUtility::GamePlayUtility()
{
}

GamePlayUtility::~GamePlayUtility()
{
}

void GamePlayUtility::TickPrint(UObject* obj, enum ETickingGroup tick)
{
	TArray<FStringFormatArg> FormatArray;
	FormatArray.Add(FStringFormatArg(GFrameNumber));
	FormatArray.Add(FStringFormatArg(GFrameCounter));
	FormatArray.Add(FStringFormatArg(obj->GetFName().GetPlainNameString()));
	FormatArray.Add(FStringFormatArg(obj->GetName()));
	//FormatArray.Add(FStringFormatArg(obj->GetFullName()));
	FormatArray.Add(FStringFormatArg(obj->GetFullGroupName(true)));


	const UEnum* groupEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETickingGroup"));

	FString sname = groupEnum->GetDisplayNameText((int)tick).ToString();
	//FString sname = groupEnum->GetEnumName(tick);
	FormatArray.Add(FStringFormatArg(sname));

	FString s = FString::Format(TEXT("UGamePlayActorComponent Tick -- {0}  --  {1} -- {2} -- {3} -- {4} -- {5} "), FormatArray);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, s);
}