// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyOverlay.h"
#include "BurnBoats/Character/StartUp/LobbyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "BurnBoats/GameBase/StartUp/LobbyGameMode.h"
#include "Net/UnrealNetwork.h"

void ULobbyOverlay::OnClick_ToggleReady()
{
	if (ALobbyPlayerController* PC = Cast<ALobbyPlayerController>(GetOwningPlayer()))
	{
		PC->Server_ToggleReady();
	}
}

void ULobbyOverlay::OnClick_StartGame()
{
	// 只有服务器有权调用 GameMode 的函数
	if (GetWorld()->GetNetMode() == NM_ListenServer || GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		if (ALobbyGameMode* GM = Cast<ALobbyGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			GM->AttemptStartGame();
		}
	}
}