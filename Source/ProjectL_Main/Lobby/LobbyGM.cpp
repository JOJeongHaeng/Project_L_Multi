// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGM.h"
#include "LobbyGS.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


void ALobbyGM::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	//ErrorMessage = TEXT("get out here.");

	UE_LOG(LogTemp, Warning, TEXT("PreLogin : %s %s"), *Options, *Address);
}

APlayerController* ALobbyGM::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	UE_LOG(LogTemp, Warning, TEXT("Login : %d %s"), InRemoteRole, *Options);

	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
}

void ALobbyGM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogTemp, Warning, TEXT("PostLogin : %s"), *NewPlayer->GetName());

	CountConnect();
}

void ALobbyGM::Logout(AController* Exiting)
{
	CountConnect();
}

void ALobbyGM::CountConnect()
{
	uint16 ConnectCount = 0;
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		ConnectCount++;
	}

	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		GS->ConnectCount = ConnectCount;
		GS->OnRep_ConnectCount(); //Server, client auto execute
	}
}

void ALobbyGM::BeginPlay()
{
	Super::BeginPlay();

	//UKismetSystemLibrary::K2_SetTimer(this, TEXT("DecreaseTime"), 1.0f, true);

	//C++
	GetWorld()->GetTimerManager().SetTimer(
		LeftTimeHandle,
		this,
		&ALobbyGM::DecreaseTime,
		1.0f,
		true
	);
}

void ALobbyGM::DecreaseTime()
{
	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		GS->LeftTime--;
		if (GS->LeftTime == 0)
		{
			//UKismetSystemLibrary::K2_ClearTimer(this, TEXT("DecreaseTime"));
			GetWorld()->GetTimerManager().ClearTimer(LeftTimeHandle);
		}
		GS->LeftTime = FMath::Clamp(GS->LeftTime, 0, 60);
		GS->OnRep_LeftTime(); //Server, client auto execute
	}
}


void ALobbyGM::StartGame()
{
	GetWorld()->ServerTravel(TEXT("Map_L"));
}