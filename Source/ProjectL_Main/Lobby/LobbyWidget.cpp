// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "LobbyPC.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyGS.h"
#include "LobbyGM.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &ULobbyWidget::Start);
	}

	if (ChatEnterButton)
	{
		ChatEnterButton->OnClicked.AddDynamic(this, &ULobbyWidget::EnterChat);
	}

	if (ChatInput)
	{
		ChatInput->OnTextChanged.AddDynamic(this, &ULobbyWidget::OnChangedEvent);
		ChatInput->OnTextCommitted.AddDynamic(this, &ULobbyWidget::OnCommittedEvent);
	}
}

void ULobbyWidget::Start()
{
	ALobbyGM* GM = Cast<ALobbyGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->StartGame();
	}
}

void ULobbyWidget::EnterChat()
{
	ALobbyPC* PC = Cast<ALobbyPC>(GetOwningPlayer());
	if (PC)
	{
		PC->C2S_SendMessage(ChatInput->GetText());
	}

}

void ULobbyWidget::OnChangedEvent(const FText& Text)
{
	FString Temp = Text.ToString();

	Temp = Temp.Replace(TEXT("¹Ùº¸"), TEXT("**"));

	ChatInput->SetText(FText::FromString(Temp));

	UE_LOG(LogTemp, Warning, TEXT("%s"), *Temp);

}

void ULobbyWidget::OnCommittedEvent(const FText& Text, ETextCommit::Type CommitMethod)
{
	switch (CommitMethod)
	{
	case ETextCommit::OnEnter:
	{
		ALobbyPC* PC = Cast<ALobbyPC>(GetOwningPlayer());
		if (PC)
		{
			PC->C2S_SendMessage(ChatInput->GetText());
			ChatInput->SetText(FText::FromString(TEXT("")));
		}
	}
	case ETextCommit::OnCleared:
	{
		ChatInput->SetUserFocus(GetOwningPlayer());
	}
	}
}

void ULobbyWidget::ShowStartButton()
{
	if (StartButton)
	{
		StartButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void ULobbyWidget::AddMessage(const FText& Text)
{
	UTextBlock* NewMessage = NewObject<UTextBlock>(ChatScroll);
	if (IsValid(NewMessage))
	{
		NewMessage->SetText(Text);
		FSlateFontInfo NewFont = NewMessage->GetFont();
		NewFont.Size = 18;
		NewMessage->SetFont(NewFont);

		ChatScroll->AddChild(NewMessage);
		ChatScroll->ScrollToEnd();
	}
}

void ULobbyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

