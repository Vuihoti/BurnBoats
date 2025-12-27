// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TipOverlay.generated.h"

/**
 * 
 */
UCLASS()
class BURNBOATS_API UTipOverlay : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativePreConstruct() override;

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BTN;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Title;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MSG;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T1;

	UFUNCTION()
	void BTNPressed();

	UFUNCTION()
	void BTN1Hover();

	UFUNCTION()
	void BTN1UnHover();

	UFUNCTION()
	void Update(FString TitleText, FString MSGText);
};
