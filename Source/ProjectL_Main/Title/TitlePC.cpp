// Fill out your copyright notice in the Description page of Project Settings.


#include "TitlePC.h"
#include "Kismet/GameplayStatics.h"

void ATitlePC::StartServer()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Lobby"), true, TEXT("listen"));
}

void ATitlePC::ConnectClient(FText ServerIP)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(ServerIP.ToString()), true, TEXT("Hello"));
}
