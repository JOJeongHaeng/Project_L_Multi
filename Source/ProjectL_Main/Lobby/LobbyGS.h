// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGS.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTL_MAIN_API ALobbyGS : public AGameStateBase
{
	GENERATED_BODY()
public:

	UPROPERTY(ReplicatedUsing = "OnRep_LeftTime")
	uint16 LeftTime = 60;

	UPROPERTY(ReplicatedUsing = OnRep_ConnectCount)
	uint16 ConnectCount = 0;

	UFUNCTION()
	void OnRep_LeftTime();

	UFUNCTION()
	void OnRep_ConnectCount();


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
