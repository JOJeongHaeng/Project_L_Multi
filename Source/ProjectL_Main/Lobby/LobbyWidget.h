// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class UScrollBox;
class UButton;
class UTextBlock;
class UEditableTextBox;

/**
 *
 */
UCLASS()
class PROJECTL_MAIN_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidgetOptional), VisibleAnywhere, Category = "UI", BlueprintReadOnly)
	TObjectPtr<UTextBlock> LeftTimeText;

	UPROPERTY(meta = (BindWidgetOptional), VisibleAnywhere, Category = "UI", BlueprintReadOnly)
	TObjectPtr<UTextBlock> ConnectCountText;

	UPROPERTY(meta = (BindWidgetOptional), VisibleAnywhere, Category = "UI", BlueprintReadOnly)
	TObjectPtr<UButton> ChatEnterButton;

	UPROPERTY(meta = (BindWidgetOptional), VisibleAnywhere, Category = "UI", BlueprintReadOnly)
	TObjectPtr<UButton> StartButton;

	UPROPERTY(meta = (BindWidgetOptional), VisibleAnywhere, Category = "UI", BlueprintReadOnly)
	TObjectPtr<UScrollBox> ChatScroll;

	UPROPERTY(meta = (BindWidgetOptional), VisibleAnywhere, Category = "UI", BlueprintReadOnly)
	TObjectPtr<UEditableTextBox> ChatInput;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void Start();

	UFUNCTION()
	void EnterChat();

	UFUNCTION()
	void OnChangedEvent(const FText& Text);

	UFUNCTION()
	void OnCommittedEvent(const FText& Text, ETextCommit::Type CommitMethod);

	void ShowStartButton();

	void AddMessage(const FText& Text);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


};
