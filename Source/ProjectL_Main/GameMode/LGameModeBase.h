// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTL_MAIN_API ALGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ALGameModeBase();

protected:
    virtual void BeginPlay() override;
    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void Logout(AController* Exiting) override;
	
};
