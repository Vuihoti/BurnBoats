// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BurnBoats/Character/PlayerStateBase.h"
#include "StartUpPlayerState.generated.h"

// 玩家信息结构体，用于UI显示
USTRUCT(BlueprintType)
struct FPlayerInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString PlayerName;

    UPROPERTY(BlueprintReadOnly)
    int32 PlayerID;

    UPROPERTY(BlueprintReadOnly)
    bool bIsHost;

    UPROPERTY(BlueprintReadOnly)
    float Ping;

    FPlayerInfo()
        : PlayerName(TEXT("Unknown"))
        , PlayerID(-1)
        , bIsHost(false)
        , Ping(0.0f)
    {
    }

    FPlayerInfo(const FString& Name, int32 ID, bool bHost = false)
        : PlayerName(Name)
        , PlayerID(ID)
        , bIsHost(bHost)
        , Ping(0.0f)
    {
    }
};

// 委托声明
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerNameChanged, const FString&, NewName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerReadyChanged, bool, bIsReady);

/**
 * 
 */
UCLASS()
class BURNBOATS_API AStartUpPlayerState : public APlayerStateBase
{
	GENERATED_BODY()
public:

};
