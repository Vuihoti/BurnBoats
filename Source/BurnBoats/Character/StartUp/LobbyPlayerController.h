// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BurnBoats/Character/PlayerControllerBase.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BURNBOATS_API ALobbyPlayerController : public APlayerControllerBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	// 请求服务器设置名字
	UFUNCTION(Server, Reliable)
	void Server_SetPlayerName(const FString& InName);

	// 请求服务器切换准备状态
	UFUNCTION(Server, Reliable)
	void Server_ToggleReady();
};
