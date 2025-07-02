// Fill out your copyright notice in the Description page of Project Settings.


#include "GimmicFailedPlane.h"

#include"Components/StaticMeshComponent.h"
#include"Components/SphereComponent.h"


// Sets default values
AGimmicFailedPlane::AGimmicFailedPlane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = RootBox;
	RootBox = CreateDefaultSubobject<USphereComponent>(TEXT("RootBox"));
	RootBox->SetCollisionProfileName(TEXT("OverlapAll"));
	
	Floor =CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	Floor->SetupAttachment(RootBox);



}

void AGimmicFailedPlane::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		ApplyDamage = true;
	}
}

void AGimmicFailedPlane::EndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		ApplyDamage = false;
	}
}
			


// Called when the game starts or when spawned
void AGimmicFailedPlane::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, & AGimmicFailedPlane::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, & AGimmicFailedPlane::EndOverlap);

}

// Called every frame
void AGimmicFailedPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DamageTime += DeltaTime;

	if (ApplyDamage && DamageTime>1)
	{
		DamageTime = 0; 

	}
}

