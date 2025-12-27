// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyOverlay.generated.h"

/**
 * 
 */
UCLASS()
class BURNBOATS_API ULobbyOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	// 供蓝图调用，切换准备状态
	UFUNCTION(BlueprintCallable, Category = "Lobby UI")
	void OnClick_ToggleReady();

	// 供蓝图调用，房主点击开始游戏
	UFUNCTION(BlueprintCallable, Category = "Lobby UI")
	void OnClick_StartGame();

	// 在蓝图中实现：刷新玩家列表UI的视觉效果
	// 你可以在这里获取 GameState->PlayerArray 并生成 ScrollBox 的子项
	UFUNCTION(BlueprintImplementableEvent, Category = "Lobby UI")
	void RefreshPlayerList();
};
