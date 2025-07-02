// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GimmicFailedPlane.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class PROJECTL_MAIN_API AGimmicFailedPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGimmicFailedPlane();

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadWrite)
	TObjectPtr<USphereComponent> RootBox;

		UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadWrite)
		TObjectPtr<UStaticMeshComponent> Floor;
	
		UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

		UFUNCTION()
		void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);

		UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
		bool ApplyDamage =false;

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		float DamageTime;

	};
