// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGS.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyPC.h"
#include "LobbyWidget.h"
#include "Components/TextBlock.h"

void ALobbyGS::OnRep_LeftTime()
{
	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PC)
	{
		FString Temp = FString::Printf(TEXT("%d초 남음"), LeftTime);
		if (PC->WidgetObject)
		{
			PC->WidgetObject->LeftTimeText->SetText(FText::FromString(Temp));
		}
	}
}

void ALobbyGS::OnRep_ConnectCount()
{
	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PC)
	{
		FString Temp = FString::Printf(TEXT("%d명 접속"), ConnectCount);
		if (PC->WidgetObject)
		{
			PC->WidgetObject->ConnectCountText->SetText(FText::FromString(Temp));
		}
	}

}

void ALobbyGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGS, LeftTime);
	DOREPLIFETIME(ALobbyGS, ConnectCount);
}
