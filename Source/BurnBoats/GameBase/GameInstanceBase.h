// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "GameInstanceBase.generated.h"

UCLASS()
class BURNBOATS_API UGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

public:
    UGameInstanceBase();

	// 玩家名称
	UPROPERTY(BlueprintReadWrite, Category = "Player")
	FString PlayerName;

	// 会话管理
	void CreateSession(FName SessionName, FString GameMode);

	void FindSessions();

	void JoinSession(const FOnlineSessionSearchResult& SessionResult);

	void DestroySession();

	// 通过IP地址加入
	void JoinByIP(const FString& IPAddress);

	// 启动游戏
	void StartGame();

	// 获取当前会话的IP地址
	FString GetCurrentSessionIP() const;

protected:
	virtual void Init() override;

private:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSettings> SessionSettings;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	// 委托绑定
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;

	FDelegateHandle CreateSessionCompleteDelegateHandle;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	FDelegateHandle DestroySessionCompleteDelegateHandle;

	// 委托回调函数
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
};
