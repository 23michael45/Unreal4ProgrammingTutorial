// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"
#include "Runtime/Engine/Public/EngineUtils.h"

AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TotalDamage = 200;
	DamageTimeInSeconds = 1.f;

	SafeObject = NewObject<UMyGCType>();
	DoomedObject = NewObject<UMyGCType>();
}

void AMyActor::PostInitProperties()
{
	Super::PostInitProperties();
	CalculateValues();
}

void AMyActor::CalculateValues()
{
	DamagePerSecond = TotalDamage / DamageTimeInSeconds;
}

#if WITH_EDITOR
void AMyActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	CalculateValues();

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	

	// Will find ALL current UObject instances
	for (TObjectIterator<UObject> It; It; ++It)
	{
		UObject* CurrentObject = *It;
		UE_LOG(LogTemp, Log, TEXT("Found UObject named: %s"), *CurrentObject->GetName());
	}


	UWorld* World = this->GetWorld();

	// Like object iterators, you can provide a specific class to get only objects that are
	// or derive from that class
	for (TActorIterator<AMyActor> It(World); It; ++It)
	{
		// ...
		UE_LOG(LogTemp, Log, TEXT("Found UObject named: %s"), *It->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *It->GetName());
	}
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AMyActor::CalledFromNativeCpp_Implementation()
//{
//	// Do something cool here
//}
//void AMyActor::CalledFromImplementCpp_Implementation()
//{
//	// Do something cool here
//}