// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ModeSelectionOverlay.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EMode : uint8
{
	EM_Rush               UMETA(DisplayName = "Rush"),
	EM_TeamCompetition    UMETA(DisplayName = "TeamCompetition"),
	EM_KingOfTheHills     UMETA(DisplayName = "KingOfTheHills")
};

USTRUCT(BlueprintType)
struct FModeData : public FTableRowBase {
	GENERATED_BODY();

	UPROPERTY(EditAnywhere)
	FText ModeTitle;

	UPROPERTY(EditAnywhere)
	FText ModeIntroduction;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* ModePicture;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnModeSelection, EMode, ModeName);

UCLASS()
class BURNBOATS_API UModeSelectionOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void InitMode();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BTN;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Picture;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Hover;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ModeTitle;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ModeIntroduction;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* HoverAnim;

	UPROPERTY(EditAnywhere)
	EMode ModeSelection;

	UPROPERTY(BlueprintAssignable)
	FOnModeSelection ModeSelectionAction;

	UPROPERTY()
	UDataTable* ModeDataTable;

	UFUNCTION()
	void Click();

	UFUNCTION()
	void UnClick();

	UFUNCTION()
	void BTNHover();

	UFUNCTION()
	void BTNUnHover();
};
