// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceBase.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"
#include "Kismet/GamePlayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/GameUserSettings.h"
void UGameInstanceBase::LoadingLocalSettings()
{
	GameLocalSetting = UGameUserSettings::GetGameUserSettings();
	switch (GameLocalSetting->GetFullscreenMode())
	{
	case EWindowMode::Fullscreen:
		OnlinePlayerSet.WindowMode = "FullScreen";
		break;
	case EWindowMode::WindowedFullscreen:
		OnlinePlayerSet.WindowMode = "WindowedFullscreen";
		break;
	case EWindowMode::Windowed:
		OnlinePlayerSet.WindowMode = "Windowed";
		break;
	}
	OnlinePlayerSet.Resolution = GameLocalSetting->GetScreenResolution();
	if (GameLocalSetting->GetFrameRateLimit() == 1000.f) {
		OnlinePlayerSet.MaxFPS = "NoLimit";
	}
	else {
		OnlinePlayerSet.MaxFPS = FString::FromInt(GameLocalSetting->GetFrameRateLimit());
	}
	OnlinePlayerSet.VSync = GameLocalSetting->IsVSyncEnabled();

	OnlinePlayerSet.ViewDistance = GameLocalSetting->GetViewDistanceQuality();
	OnlinePlayerSet.GlobalIllumination = GameLocalSetting->GetGlobalIlluminationQuality();
	OnlinePlayerSet.AntiAliasing = GameLocalSetting->GetAntiAliasingQuality();
	OnlinePlayerSet.PostProcessing = GameLocalSetting->GetPostProcessingQuality();
	OnlinePlayerSet.Reflection = GameLocalSetting->GetReflectionQuality();
	OnlinePlayerSet.Texture = GameLocalSetting->GetTextureQuality();
	OnlinePlayerSet.Shadow = GameLocalSetting->GetShadowQuality();
	OnlinePlayerSet.Shading = GameLocalSetting->GetShadingQuality();

	if (UGameplayStatics::DoesSaveGameExist("SG_Setting", 0)) {
		SaveGameSetting = Cast<USaveGameSetting>(UGameplayStatics::LoadGameFromSlot("SG_Setting", 0));
		OnlinePlayerSet = SaveGameSetting->LocalGameSetting;
	}
	else {
		SaveGameSetting == nullptr ? Cast<USaveGameSetting>(UGameplayStatics::CreateSaveGameObject(USaveGameSetting::StaticClass())) : SaveGameSetting;
		SaveGameSetting->LocalGameSetting = OnlinePlayerSet;
		UGameplayStatics::SaveGameToSlot(SaveGameSetting, "SG_Setting", 0);
	}
}

void UGameInstanceBase::LoadingLocalArchive()
{
	if (!UGameplayStatics::DoesSaveGameExist("SG_Player", 0))
	{
		CreateANewArchive();
	}
	SavePlayerData = Cast<USaveGamePlayer>(UGameplayStatics::LoadGameFromSlot("SG_Player", 0));
	if (SavePlayerData)
	{
		OnlinePlayerData = SavePlayerData->PlayerData;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load player archive!"));
	}

}

void UGameInstanceBase::SaveLocalArchive()
{
	SavePlayerData = Cast<USaveGamePlayer>(UGameplayStatics::LoadGameFromSlot("SG_Player", 0));
	SavePlayerData->PlayerData = OnlinePlayerData;
	UGameplayStatics::SaveGameToSlot(SavePlayerData, "SG_Player", 0);
}

void UGameInstanceBase::SaveLocalGameSetting()
{
	if (UGameplayStatics::DoesSaveGameExist("SG_Setting", 0)) {
		SaveGameSetting = Cast<USaveGameSetting>(UGameplayStatics::LoadGameFromSlot("SG_Setting", 0));
		SaveGameSetting->LocalGameSetting = OnlinePlayerSet;
		UGameplayStatics::SaveGameToSlot(SaveGameSetting, "SG_Setting", 0);
	}
}

void UGameInstanceBase::CreateANewArchive()
{
	SavePlayerData = Cast<USaveGamePlayer>(UGameplayStatics::CreateSaveGameObject(USaveGamePlayer::StaticClass()));
	SavePlayerData->PlayerData = OnlinePlayerData;
	UGameplayStatics::SaveGameToSlot(SavePlayerData, "SG_Player", 0);
}
