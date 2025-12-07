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

void UStartUpOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	btn_LANBattle->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN1Hover);
	btn_Shootingrange->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN2Hover);
	btn_GameSetting->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN3Hover);
	btn_ListOfDevelopers->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN4Hover);
	btn_Quit->OnHovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN5Hover);

	btn_LANBattle->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN1UnHover);
	btn_Shootingrange->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN2UnHover);
	btn_GameSetting->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN3UnHover);
	btn_ListOfDevelopers->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN4UnHover);
	btn_Quit->OnUnhovered.AddUniqueDynamic(this, &UStartUpOverlay::BTN5UnHover);

	btn_LANBattle->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_LANBattlePressed);
	btn_Shootingrange->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_ShootingrangePressed);
	btn_ListOfDevelopers->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_ListOfDevelopersPressed);
	btn_GameSetting->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_GameSettingPressed);
	btn_Quit->OnClicked.AddUniqueDynamic(this, &UStartUpOverlay::btn_QuitPressed);
}

void UStartUpOverlay::btn_LANBattlePressed()
{
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

void UStartUpOverlay::BTN1Hover()
{
	T1->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN2Hover()
{
	T2->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN3Hover()
{
	T3->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN4Hover()
{
	T4->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN5Hover()
{
	T5->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UStartUpOverlay::BTN1UnHover()
{
	T1->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}

void UStartUpOverlay::BTN2UnHover()
{
	T2->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}

void UStartUpOverlay::BTN3UnHover()
{
	T3->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}

void UStartUpOverlay::BTN4UnHover()
{
	T4->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}

void UStartUpOverlay::BTN5UnHover()
{
	T5->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
}