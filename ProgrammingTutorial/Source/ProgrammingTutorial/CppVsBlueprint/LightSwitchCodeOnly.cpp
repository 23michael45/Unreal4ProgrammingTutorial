// Fill out your copyright notice in the Description page of Project Settings.

#include "LightSwitchCodeOnly.h"

ALightSwitchCodeOnly::ALightSwitchCodeOnly()
{	
// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DesiredIntensity = 3000.0f;

	PointLight1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	PointLight1->Intensity = DesiredIntensity;
	PointLight1->bVisible = true;
	RootComponent = PointLight1;

	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"));
	Sphere1->InitSphereRadius(250.0f);
	Sphere1->SetupAttachment(RootComponent);

	Sphere1->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitchCodeOnly::OnOverlapBegin);       // set up a notification for when this component overlaps something
	Sphere1->OnComponentEndOverlap.AddDynamic(this, &ALightSwitchCodeOnly::OnOverlapEnd);       // set up a notification for when this component overlaps something

}
void ALightSwitchCodeOnly::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void ALightSwitchCodeOnly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	TArray<AActor*> arr;

	Sphere1->GetOverlappingActors(arr, TSubclassOf<AActor>());

	if (arr.Num() > 0)
	{

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("GetOverlappingActors true!"));
		PointLight1->SetVisibility(false);
	}
	else
	{

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("GetOverlappingActors false!"));
		PointLight1->SetVisibility(true);
	}

}
void ALightSwitchCodeOnly::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}

void ALightSwitchCodeOnly::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}

void ALightSwitchCodeOnly::ToggleLight()
{
	PointLight1->ToggleVisibility();
}
