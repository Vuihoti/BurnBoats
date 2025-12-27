// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerController.h"
#include "BurnBoats/GameBase/GameInstanceBase.h"
#include "LobbyPlayerState.h"

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 如果是本地玩家，从GameInstance读取名字并发给服务器
	if (IsLocalPlayerController())
	{
		UGameInstanceBase* GI = Cast<UGameInstanceBase>(GetGameInstance());
		if (GI && !GI->OnlinePlayerData.PlayerName.IsEmpty())
		{
			Server_SetPlayerName(GI->OnlinePlayerData.PlayerName);
		}
	}
}

void ALobbyPlayerController::Server_SetPlayerName_Implementation(const FString& InName)
{
	if (ALobbyPlayerState* PS = GetPlayerState<ALobbyPlayerState>())
	{
		PS->LobbyPlayerName = InName;
		// 强制更新一次同步，确保名字立即显示
		PS->OnRep_LobbyInfo();
	}
}

void ALobbyPlayerController::Server_ToggleReady_Implementation()
{
	if (ALobbyPlayerState* PS = GetPlayerState<ALobbyPlayerState>())
	{
		PS->bIsReady = !PS->bIsReady;
		PS->OnRep_LobbyInfo(); // 手动调用以触发服务器端的UI更新（如果服务器也是玩家）
	}
}
