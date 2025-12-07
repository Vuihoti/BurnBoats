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
	class UTextBlock* T1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T4;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T5;

	UFUNCTION(BlueprintCallable)
	void btn_LANBattlePressed();

	UFUNCTION(BlueprintCallable)
	void btn_ShootingrangePressed();

	UFUNCTION(BlueprintCallable)
	void btn_GameSettingPressed();

	UFUNCTION(BlueprintCallable)
	void btn_ListOfDevelopersPressed();

	UFUNCTION(BlueprintCallable)
	void btn_QuitPressed();

	UFUNCTION(BlueprintCallable)
	void BTN1Hover();

	UFUNCTION(BlueprintCallable)
	void BTN2Hover();

	UFUNCTION(BlueprintCallable)
	void BTN3Hover();

	UFUNCTION(BlueprintCallable)
	void BTN4Hover();

	UFUNCTION(BlueprintCallable)
	void BTN5Hover();

	UFUNCTION(BlueprintCallable)
	void BTN1UnHover();

	UFUNCTION(BlueprintCallable)
	void BTN2UnHover();

	UFUNCTION(BlueprintCallable)
	void BTN3UnHover();

	UFUNCTION(BlueprintCallable)
	void BTN4UnHover();

	UFUNCTION(BlueprintCallable)
	void BTN5UnHover();

	UPROPERTY(BlueprintReadOnly)
	class AHUDBase* HUD;
	//Resource

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	TSubclassOf<UUserWidget> GameSetOverlayclass;

	UPROPERTY()
	class UGameInstanceBase* GameInstance;
};
