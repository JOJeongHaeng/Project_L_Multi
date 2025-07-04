// Fill out your copyright notice in the Description page of Project Settings.


#include "DevelopGameModeBase.h"

ADevelopGameModeBase::ADevelopGameModeBase()
{
}

void ADevelopGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("GameMode: BeginPlay on Server"));
}

void ADevelopGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Log, TEXT("Player joined: %s"), *NewPlayer->GetName());
}

void ADevelopGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	UE_LOG(LogTemp, Log, TEXT("Player left: %s"), *Exiting->GetName());
}
