// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "GameFramework/SaveGame.h"
#include "GameInstanceBase.generated.h"

USTRUCT(BlueprintType)
struct FGameSets
{
	GENERATED_BODY();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool FirstTime = true;

	//帧数显示
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	bool ShowFPS = false;

	//垂直同步
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	bool VSync = true;

	//最大帧数
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	FString MaxFPS = "60";

	//分辨率
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	FIntPoint Resolution = { 1920,1080 };

	//窗口模式
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	FString WindowMode = "FullScreen";

	//是否启用DLSS
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	bool bDLSS = false;

	//光线追踪品质
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	int32 DLSSQuality = 2;

	//是否启用DLSS帧生成
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	bool bFrameGeneration = false;

	//是否启用光线追踪
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	bool bRayTracing = false;

	//光线追踪品质
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	int32 RayTracingQuality = 1;

	//是否启用动态模糊
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	bool bMotionBlur = true;


	//视距
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	int32 ViewDistance = 2;

	//抗锯齿
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	int32 AntiAliasing = 2;

	//后期处理
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	int32 PostProcessing = 2;

	//阴影
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	int32 Shadow = 2;

	//全局光照
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	int32 GlobalIllumination = 2;

	//反射
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	int32 Reflection = 2;

	//纹理
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	int32 Texture = 2;

	//着色
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Screen")
	int32 Shading = 2;


	//灵敏度
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	float MouseSensitivity = 0.4f;


	//总音量
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Volume")
	float TotalVolume = 1.f;

	//背景音量
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Volume")
	float BackgroundVolume = 1.f;

	//音效音量
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Volume")
	float SoundEffectVolume = 1.f;

	//语音音量
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Volume")
	float VoiceVolume = 1.f;
};

USTRUCT(BlueprintType)
struct FPlayerData {
	GENERATED_BODY();

public:
	FString PlayerName;
};

UCLASS()
class BURNBOATS_API USaveGameSetting : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FGameSets LocalGameSetting;
};

UCLASS()
class BURNBOATS_API USaveGamePlayer : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FPlayerData PlayerData;
};


UCLASS()
class BURNBOATS_API UGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UGameUserSettings* GameLocalSetting;

	//游戏线上数据
	UPROPERTY(BlueprintReadWrite)
	FGameSets OnlinePlayerSet;

	UPROPERTY(BlueprintReadWrite)
	FPlayerData OnlinePlayerData;

	//本地内存数据
	UPROPERTY(BlueprintReadOnly)
	USaveGameSetting* SaveGameSetting;

	UPROPERTY(BlueprintReadOnly)
	USaveGamePlayer* SavePlayerData;

	UFUNCTION(BlueprintCallable)
	void LoadingLocalSettings();

	UFUNCTION(BlueprintCallable)
	void LoadingLocalArchive();

	UFUNCTION(BlueprintCallable)
	void SaveLocalArchive();

	UFUNCTION(BlueprintCallable)
	void SaveLocalGameSetting();

	UFUNCTION(BlueprintCallable)
	void CreateANewArchive();
};
