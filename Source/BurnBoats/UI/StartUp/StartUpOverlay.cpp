// Fill out your copyright notice in the Description page of Project Settings.


#include "StartUpOverlay.h"
#include "Components/Button.h"
//#include "GameSetOverlay.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/TextBlock.h"
#include "Styling/SlateColor.h"
#include "Kismet/GameplayStatics.h"
#include "BurnBoats/GameBase/GameInstanceBase.h"
#include "BurnBoats/UI/HUDBase.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableText.h"
#include "Components/Slider.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "GameFramework/GameUserSettings.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"
#include "Components/WidgetSwitcher.h"
#include "RHI.h"
#include "Components/EditableTextBox.h"
#include "BurnBoats/UI/TipOverlay.h"

void UStartUpOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	btn_LANBattle->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN1Hover);
	btn_Shootingrange->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN2Hover);
	btn_GameSetting->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN3Hover);
	btn_ListOfDevelopers->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN4Hover);
	btn_Quit->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN5Hover);
	btn_Join->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN6Hover);
	btn_Host->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN7Hover);
	btn_Return1->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN8Hover);
	btn_Return2->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN9Hover);
	btn_JoinRoom->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN10Hover);
	btn_Return3->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN11Hover);

	btn_LANBattle->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN1UnHover);
	btn_Shootingrange->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN2UnHover);
	btn_GameSetting->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN3UnHover);
	btn_ListOfDevelopers->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN4UnHover);
	btn_Quit->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN5UnHover);
	btn_Join->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN6UnHover);
	btn_Host->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN7UnHover);
	btn_Return1->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN8UnHover);
	btn_Return2->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN9UnHover);
	btn_JoinRoom->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN10UnHover);
	btn_Return3->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN11UnHover);

	btn_LANBattle->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_LANBattlePressed);
	btn_Shootingrange->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_ShootingrangePressed);
	btn_ListOfDevelopers->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_ListOfDevelopersPressed);
	btn_GameSetting->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_GameSettingPressed);
	btn_Quit->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_QuitPressed);
	btn_Return1->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_Return1Pressed);
	btn_Return2->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_LANBattlePressed);
	btn_Return3->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_LANBattlePressed);
	btn_Join->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_JoinPressed);
	btn_Host->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_HostPressed);
	btn_JoinRoom->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_JoinRoomPressed);
	btn_HostRoom->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_HostRoomPressed);

	ETB_PlayerName->OnTextChanged.AddUniqueDynamic(this, &UStartUpOverlay::SavePLayerName);
	GameInstanceBase = Cast<UGameInstanceBase>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstanceBase) {
		//读存档，读配置
		GameInstanceBase->LoadingLocalArchive();
		GameInstanceBase->LoadingLocalSettings();
		if (!GameInstanceBase->OnlinePlayerData.PlayerName.IsEmpty()) {
			ETB_PlayerName->SetText(FText::FromString(GameInstanceBase->OnlinePlayerData.PlayerName));
		}
	}

}

void UStartUpOverlay::btn_LANBattlePressed()
{
	Switcher->SetActiveWidgetIndex(1);
}

void UStartUpOverlay::btn_ShootingrangePressed()
{
}

void UStartUpOverlay::btn_GameSettingPressed()
{
}

void UStartUpOverlay::btn_ListOfDevelopersPressed()
{
}

void UStartUpOverlay::btn_QuitPressed()
{
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		EQuitPreference::Quit,
		false
	);
}

void UStartUpOverlay::btn_Return1Pressed()
{
	Switcher->SetActiveWidgetIndex(0);
}

void UStartUpOverlay::btn_JoinPressed()
{
	if (ETB_PlayerName->GetText().IsEmpty()) PrintTip(TEXT("操作失败"), TEXT("请先输入昵称！"));
	else Switcher->SetActiveWidgetIndex(2);
}

void UStartUpOverlay::btn_HostPressed()
{
	if (ETB_PlayerName->GetText().IsEmpty()) PrintTip(TEXT("操作失败"), TEXT("请先输入昵称！"));
	else Switcher->SetActiveWidgetIndex(3);
}

void UStartUpOverlay::btn_JoinRoomPressed()
{
}

void UStartUpOverlay::btn_HostRoomPressed()
{
}

// Hover函数实现 - 鼠标悬停时设置为白色
void UStartUpOverlay::BTN1Hover()
{
	if (T1) T1->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN2Hover()
{
	if (T2) T2->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN3Hover()
{
	if (T3) T3->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN4Hover()
{
	if (T4) T4->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN5Hover()
{
	if (T5) T5->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN6Hover()
{
	if (T6) T6->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN7Hover()
{
	if (T7) T7->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN8Hover()
{
	if (T8) T8->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN9Hover()
{
	if (T9) T9->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN10Hover()
{
	if (T10) T10->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN11Hover()
{
	if (T11) T11->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN12Hover()
{
	if (T12) T12->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}


void UStartUpOverlay::BTN1UnHover()
{
	if (T1) T1->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}

void UStartUpOverlay::BTN2UnHover()
{
	if (T2) T2->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}

void UStartUpOverlay::BTN3UnHover()
{
	if (T3) T3->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}

void UStartUpOverlay::BTN4UnHover()
{
	if (T4) T4->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}

void UStartUpOverlay::BTN5UnHover()
{
	if (T5) T5->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}

void UStartUpOverlay::BTN6UnHover()
{
	if (T6) T6->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}

void UStartUpOverlay::BTN7UnHover()
{
	if (T7) T7->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}

void UStartUpOverlay::BTN8UnHover()
{
	if (T8) T8->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}

void UStartUpOverlay::BTN9UnHover()
{
	if (T9) T9->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}

void UStartUpOverlay::BTN10UnHover()
{
	if (T10) T10->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}

void UStartUpOverlay::BTN11UnHover()
{
	if (T11) T11->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f)); 
}

void UStartUpOverlay::BTN12UnHover()
{
	if (T12) T12->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}

void UStartUpOverlay::SavePLayerName(const FText& PlayerName)
{
	if (GameInstanceBase) {
		GameInstanceBase->OnlinePlayerData.PlayerName = PlayerName.ToString();
		GameInstanceBase->SaveLocalArchive();
	}
}

void UStartUpOverlay::PrintTip(const FString& Title, const FString& Message)
{
	if (!IsValid(TipOverlayclass))
	{
		UE_LOG(LogTemp, Error, TEXT("TipOverlayclass未定义！"));
		return;
	}
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Error, TEXT("无法获取有效的世界上下文"));
		return;
	}
	UTipOverlay* Widget = CreateWidget<UTipOverlay>(World, TipOverlayclass);
	if (!IsValid(Widget))
	{
		UE_LOG(LogTemp, Error, TEXT("创建UTipOverlay实例失败！"));
		return;
	}
	Widget->AddToViewport(100);
	Widget->Update(Title, Message);
}
