// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartUpOverlay.generated.h"

/**
 * 
 */
UCLASS()
class BURNBOATS_API UStartUpOverlay : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_LANBattle;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Shootingrange;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_GameSetting;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_ListOfDevelopers;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Quit;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Return1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Return2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Return3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* ETB_PlayerName;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Join;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_Host;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_JoinRoom;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* ETB_IP;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_HostRoom;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T4;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T5;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T6;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T7;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T8;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T9;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T10;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T11;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T12;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* Switcher;

	UFUNCTION()
	void btn_LANBattlePressed();

	UFUNCTION()
	void btn_ShootingrangePressed();

	UFUNCTION()
	void btn_GameSettingPressed();

	UFUNCTION()
	void btn_ListOfDevelopersPressed();

	UFUNCTION()
	void btn_QuitPressed();

	UFUNCTION()
	void btn_Return1Pressed();

	UFUNCTION()
	void btn_JoinPressed();

	UFUNCTION()
	void btn_HostPressed();

	UFUNCTION()
	void btn_JoinRoomPressed();

	UFUNCTION()
	void btn_HostRoomPressed();

	UFUNCTION()
	void BTN1Hover();

	UFUNCTION()
	void BTN2Hover();

	UFUNCTION()
	void BTN3Hover();

	UFUNCTION()
	void BTN4Hover();

	UFUNCTION()
	void BTN5Hover();

	UFUNCTION()
	void BTN6Hover();

	UFUNCTION()
	void BTN7Hover();

	UFUNCTION()
	void BTN8Hover();

	UFUNCTION()
	void BTN9Hover();

	UFUNCTION()
	void BTN10Hover();

	UFUNCTION()
	void BTN11Hover();

	UFUNCTION()
	void BTN12Hover();

	UFUNCTION()
	void BTN1UnHover();

	UFUNCTION()
	void BTN2UnHover();

	UFUNCTION()
	void BTN3UnHover();

	UFUNCTION()
	void BTN4UnHover();

	UFUNCTION()
	void BTN5UnHover();

	UFUNCTION()
	void BTN6UnHover();

	UFUNCTION()
	void BTN7UnHover();

	UFUNCTION()
	void BTN8UnHover();

	UFUNCTION()
	void BTN9UnHover();

	UFUNCTION()
	void BTN10UnHover();

	UFUNCTION()
	void BTN11UnHover();

	UFUNCTION()
	void BTN12UnHover();

	UFUNCTION()
	void SavePLayerName(const FText& PlayerName);

	UPROPERTY()
	class UGameInstanceBase* GameInstanceBase;

	UPROPERTY(BlueprintReadOnly)
	class AHUDBase* HUD;
	//Resource

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	TSubclassOf<UUserWidget> GameSetOverlayclass;

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	TSubclassOf<UUserWidget> TipOverlayclass;

	UFUNCTION()
	void PrintTip(const FString& Title, const FString& Message);
};
