// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"


class UEditableTextBox;
class UButton;
/**
 * 
 */
UCLASS()
class PROJECTL_MAIN_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(WidgetBinding), VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	TObjectPtr<UEditableTextBox> UserIdText;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	TObjectPtr<UEditableTextBox> PassWordText;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	TObjectPtr<UEditableTextBox> ServerIPText;

	UPROPERTY(meta = (WidgetBinding), VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	TObjectPtr<UButton> StartServerButton;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	TObjectPtr<UButton> ConnectButton;

	UFUNCTION()
	void OnClickServerStartButton();

	UFUNCTION()
	void OnClickConnectButton();

	void SaveUserId();
};
