// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitlePC.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTL_MAIN_API ATitlePC : public APlayerController
{
	GENERATED_BODY()
public:
	void StartServer();

	void ConnectClient(FText ServerIP);
};
