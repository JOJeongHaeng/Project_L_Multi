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

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	TSubclassOf<AActor> CameraActorClass;

	UPROPERTY()
	AActor* PlayerCamera = nullptr;



protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	// ��Ŭ�� �׼� ó�� �Լ�
	void OnRightClick(const FInputActionValue& Value);

	// ������ ��ǥ ��ǥ ����
	UFUNCTION(Server, Reliable)
	void Server_SetTargetLocation(const FVector& Location);




	FTimerHandle CameraSpawnTimerHandle;

	void SpawnPlayerCamera(); // ������ �� ����� �Լ�


	// �̵� ���� ����
	UPROPERTY()
	FVector TargetLocation;

	bool bIsMoving = false;

	// Enhanced Input ����
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* RightClickAction;
};