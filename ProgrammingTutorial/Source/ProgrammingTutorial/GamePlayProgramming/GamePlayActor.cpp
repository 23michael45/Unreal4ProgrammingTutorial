// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayActor.h"
#include "UnrealString.h"

// Sets default values
AGamePlayActor::AGamePlayActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	primitiveComponent = CreateDefaultSubobject<UGamePlayPrimitiveComponent>(TEXT("PrimitiveComponent"));
	primitiveComponent2 = CreateDefaultSubobject<UGamePlayPrimitiveComponent>(TEXT("PrimitiveComponent2"));
	primitiveComponent->SetTickGroup(TG_PrePhysics);
	primitiveComponent2->SetTickGroup(TG_EndPhysics);

	sceneComponent = CreateDefaultSubobject<UGamePlaySceneComponent>(TEXT("SceneComponent"));
	sceneComponent->SetTickGroup(TG_StartPhysics);

	actorComponent = CreateDefaultSubobject<UGamePlayActorComponent>(TEXT("PlayActorComponent-xxx!"));
	actorComponent->SetTickGroup(TG_PostUpdateWork);


	RootComponent = primitiveComponent2;

	primitiveComponent->SetupAttachment(primitiveComponent2);
	sceneComponent->SetupAttachment(primitiveComponent2);

	primitiveComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));




}

// Called when the game starts or when spawned
void AGamePlayActor::BeginPlay()
{
	Super::BeginPlay();

	TickPrint(this, tickgroupActor);
	SetTickGroup(tickgroupActor);

}

// Called every frame
void AGamePlayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	tickCount++;

	TickPrint(this, PrimaryActorTick.TickGroup);
}

