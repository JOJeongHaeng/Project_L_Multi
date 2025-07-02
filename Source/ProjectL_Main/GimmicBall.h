// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GimmicBall.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class PROJECTL_MAIN_API AGimmicBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGimmicBall();

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	TObjectPtr<USphereComponent> Root;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Body;

	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);



	UFUNCTION(BlueprintNativeEvent)

	void SpawnFailedPlane();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
