// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BurnBoats/Character/PlayerStateBase.h"
#include "LobbyPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLobbyStateChanged);
/**
 * 
 */
UCLASS()
class BURNBOATS_API ALobbyPlayerState : public APlayerStateBase
{
	GENERATED_BODY()

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	// 允许蓝图绑定此委托，当数据更新时刷新UI
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLobbyStateChanged OnLobbyInfoUpdated;

	// 同步的名字
	UPROPERTY(ReplicatedUsing = OnRep_LobbyInfo, BlueprintReadOnly, Category = "Lobby")
	FString LobbyPlayerName;

	// 同步的准备状态
	UPROPERTY(ReplicatedUsing = OnRep_LobbyInfo, BlueprintReadOnly, Category = "Lobby")
	bool bIsReady;

	// 当客户端收到服务器的数据更新时调用
	UFUNCTION()
	void OnRep_LobbyInfo() const;
};
