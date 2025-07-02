// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "LGamePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PROJECTL_MAIN_API ALGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALGamePlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bCanMove = true;


protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	// 우클릭 액션 처리 함수
	void OnRightClick(const FInputActionValue& Value);

	// 서버에 목표 좌표 전달
	UFUNCTION(Server, Reliable)
	void Server_SetTargetLocation(const FVector& Location);

	// 이동 관련 변수
	UPROPERTY()
	FVector TargetLocation;

	bool bIsMoving = false;

	// Enhanced Input 관련
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* RightClickAction;
};