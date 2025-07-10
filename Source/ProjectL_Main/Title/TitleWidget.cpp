// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "../MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TitlePC.h"

void UTitleWidget::NativeConstruct()
{
	ServerIPText = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ServerIPText")));
	PassWordText = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("PassWordText")));

	ConnectButton = Cast<UButton>(GetWidgetFromName(TEXT("ConnectButton")));

	if (StartServerButton)
	{
		StartServerButton->OnClicked.AddDynamic(this, &UTitleWidget::OnClickServerStartButton);
	}

	if (ConnectButton)
	{
		ConnectButton->OnClicked.AddDynamic(this, &UTitleWidget::OnClickConnectButton);
	}
}

void UTitleWidget::OnClickServerStartButton()
{
	UE_LOG(LogTemp, Warning, TEXT("OnClickServerStartButton"));
	SaveUserId();

	ATitlePC* PC = Cast<ATitlePC>(GetOwningPlayer());
	if (PC)
	{
		PC->StartServer();
	}
}

void UTitleWidget::OnClickConnectButton()
{
	UE_LOG(LogTemp, Warning, TEXT("OnClickConnectButton"));
	SaveUserId();

	ATitlePC* PC = Cast<ATitlePC>(GetOwningPlayer());
	if (PC && ServerIPText)
	{
		PC->ConnectClient(ServerIPText->GetText());
	}
}

void UTitleWidget::SaveUserId()
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI && UserIdText)
	{
		GI->UserID = UserIdText->GetText().ToString();
	}
}
