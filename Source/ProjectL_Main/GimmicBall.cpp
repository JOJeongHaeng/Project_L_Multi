// Fill out your copyright notice in the Description page of Project Settings.


#include "GimmicBall.h"
#include"Components/StaticMeshComponent.h"
#include"Components/SphereComponent.h"
#include"Kismet/KismetSystemLibrary.h"
#include"GimmicFailedPlane.h"

// Sets default values
AGimmicBall::AGimmicBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = Root;
	Root = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));

	Body->SetupAttachment(Root);

	Root->SetCollisionProfileName(TEXT("OverlapAll"));
	Body->SetCollisionProfileName(TEXT("OverlapAll"));


}

void AGimmicBall::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		Destroy();
	}
}

void AGimmicBall::SpawnFailedPlane_Implementation()
{
	//GetWorld()->SpawnActor<AGimmicFailedPlane>(AGimmicFailedPlane::StaticClass(), Body->K2_GetComponentToWorld());
	//Destroy();
}




// Called when the game starts or when spawned
void AGimmicBall::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AGimmicBall::BeginOverlap);
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("SpawnFailedPlane"), 25, false, false, 0, 0);
}

// Called every frame
void AGimmicBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

