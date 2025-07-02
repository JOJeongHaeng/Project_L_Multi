// Fill out your copyright notice in the Description page of Project Settings.


#include "LGameModeBase.h"

ALGameModeBase::ALGameModeBase()
{
}

void ALGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("GameMode: BeginPlay on Server"));

}

void ALGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogTemp, Log, TEXT("Player joined: %s"), *NewPlayer->GetName());
}

void ALGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	UE_LOG(LogTemp, Log, TEXT("Player left: %s"), *Exiting->GetName());
}
