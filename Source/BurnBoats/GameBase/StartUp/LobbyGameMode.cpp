// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "BurnBoats/Character/StartUp/LobbyPlayerState.h"

bool ALobbyGameMode::CheckAllPlayersReady() const
{
	// 遍历所有连接的玩家状态
	for (APlayerState* PS : GameState->PlayerArray)
	{
		ALobbyPlayerState* LobbyPS = Cast<ALobbyPlayerState>(PS);
		if (!LobbyPS || !LobbyPS->bIsReady)
		{
			return false; // 只要有一个没准备，就返回false
		}
	}
	return true;
}

void ALobbyGameMode::AttemptStartGame()
{
	if (CheckAllPlayersReady())
	{
		UWorld* World = GetWorld();
		if (World)
		{
			// 使用ServerTravel携带所有客户端跳转
			World->ServerTravel(GameplayLevelName + "?listen");
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not all players are ready!"));
	}
}