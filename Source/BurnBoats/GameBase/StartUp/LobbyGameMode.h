// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BurnBoats/GameBase/GameModeBS.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BURNBOATS_API ALobbyGameMode : public AGameModeBS
{
	GENERATED_BODY()

public:
	// 尝试开始游戏
	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void AttemptStartGame();

protected:
	// 检查是否所有玩家都准备好了
	bool CheckAllPlayersReady() const;

	// 目标游戏地图名称
	UPROPERTY(EditDefaultsOnly, Category = "Lobby")
	FString GameplayLevelName = "Map_Gameplay";
};
