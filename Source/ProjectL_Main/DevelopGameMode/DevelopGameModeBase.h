// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DevelopGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTL_MAIN_API ADevelopGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ADevelopGameModeBase();

	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	
};
