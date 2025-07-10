// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGM.generated.h"

/**
 *
 */
UCLASS()
class PROJECTL_MAIN_API ALobbyGM : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;


	virtual void Logout(AController* Exiting) override;

	void CountConnect();

	virtual void BeginPlay() override;


	UFUNCTION()
	void DecreaseTime();

	void StartGame();

	FTimerHandle LeftTimeHandle;



};
