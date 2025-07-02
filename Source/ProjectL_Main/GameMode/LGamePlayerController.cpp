


#include "LGamePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"


ALGamePlayerController::ALGamePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	PrimaryActorTick.bCanEverTick = true;
}

void ALGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Enhanced Input Subsystem에 MappingContext 등록
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (RightClickAction)
		{
			EnhancedInput->BindAction(RightClickAction, ETriggerEvent::Triggered, this, &ALGamePlayerController::OnRightClick);
		}
	}


	// 카메라 스폰을 0.5초 지연하여 실행
	if (IsLocalController())
	{
		GetWorldTimerManager().SetTimer(CameraSpawnTimerHandle, this, &ALGamePlayerController::SpawnPlayerCamera, 1.0f, false);
	}

	

}





void ALGamePlayerController::OnRightClick(const FInputActionValue& Value)
{
	FHitResult Hit;
	if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		TargetLocation = Hit.ImpactPoint;
		bIsMoving = true;

		DrawDebugSphere(GetWorld(), TargetLocation, 25.0f, 12, FColor::Green, false, 2.0f);

		Server_SetTargetLocation(TargetLocation);
	}
}

void ALGamePlayerController::Server_SetTargetLocation_Implementation(const FVector& Location)
{
	TargetLocation = Location;
	bIsMoving = true;
}

void ALGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bCanMove)
	{
		if (ACharacter* MyCharacter = Cast<ACharacter>(GetPawn()))
		{
			if (MyCharacter->GetCharacterMovement())
			{
				MyCharacter->GetCharacterMovement()->StopMovementImmediately();
			}
		}
		return;
	}



	if (!bIsMoving)
		return;

	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn)
		return;

	const FVector PawnLocation = ControlledPawn->GetActorLocation();
	const FVector Direction = (TargetLocation - PawnLocation);
	const float Distance = Direction.Size();

	const float StopThreshold = 100.0f;



	if (Distance <= StopThreshold)
	{
		bIsMoving = false;

		// 바라보게만 만들기
		if (!Direction.IsNearlyZero())
		{
			const FVector MoveDir = Direction.GetSafeNormal();
			FRotator NewControlRotation = MoveDir.Rotation();
			NewControlRotation.Pitch = 0.f;
			NewControlRotation.Roll = 0.f;
			SetControlRotation(NewControlRotation);
		}

		// 이동 정지
		ACharacter* MyCharacter = Cast<ACharacter>(ControlledPawn);
		if (MyCharacter && MyCharacter->GetCharacterMovement())
		{
			MyCharacter->GetCharacterMovement()->StopMovementImmediately();
		}

		return;
	}

	if (Direction.IsNearlyZero(1.0f))
	{
	
		return;
	}

	const FVector MoveDir = Direction.GetSafeNormal();

	if (bIsMoving)
	{
		FRotator NewControlRotation = MoveDir.Rotation();
		NewControlRotation.Pitch = 0.f;
		NewControlRotation.Roll = 0.f;
		SetControlRotation(NewControlRotation);


	}

	ControlledPawn->AddMovementInput(MoveDir, 1.0f);

}


void ALGamePlayerController::SpawnPlayerCamera()
{
	APawn* MyPawn = GetPawn();
	if (!MyPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnPlayerCamera: GetPawn() returned nullptr."));
		return;
	}

	if (!CameraActorClass)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnPlayerCamera: CameraActorClass is null."));
		return;
	}

	FVector CameraSpawnLocation = MyPawn->GetActorLocation() + FVector(-500.f, 0.f, 300.f);
	FRotator CameraSpawnRotation = (MyPawn->GetActorLocation() - CameraSpawnLocation).Rotation();

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	PlayerCamera = GetWorld()->SpawnActor<AActor>(CameraActorClass, CameraSpawnLocation, CameraSpawnRotation, Params);

	if (!PlayerCamera)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnPlayerCamera: Camera spawn failed!"));
		return;
	}

	SetViewTarget(PlayerCamera);
	UE_LOG(LogTemp, Warning, TEXT("SpawnPlayerCamera: Camera spawned and view target set."));
}
