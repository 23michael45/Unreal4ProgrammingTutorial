// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyGCType.h"
#include "MyActor.generated.h"
UCLASS()
class PROGRAMMINGTUTORIAL_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;

public:	
	UPROPERTY()
	UMyGCType * SafeObject;

	UMyGCType* DoomedObject;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		int32 TotalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float DamageTimeInSeconds;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Damage")
		float DamagePerSecond;
	
private:
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void CalculateValues();


	/*UFUNCTION(BlueprintNativeEvent, Category = "Damage")
		void CalledFromNativeCpp();
	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
		void CalledFromImplementCpp();*/


#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
#endif
};
