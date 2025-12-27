// Fill out your copyright notice in the Description page of Project Settings.


#include "ModeSelectionOverlay.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/DataTable.h"

void UModeSelectionOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	BTN->OnHovered.AddUniqueDynamic(this, &UModeSelectionOverlay::BTNHover);
	BTN->OnUnhovered.AddUniqueDynamic(this, &UModeSelectionOverlay::BTNUnHover);
	InitMode();
}

void UModeSelectionOverlay::InitMode()
{
    // 1. 加载数据表并检查有效性
    ModeDataTable = LoadObject<UDataTable>(this, TEXT("DataTable'/Game/UMG/StartUp/ModeDataTable.ModeDataTable'"));
    if (!ModeDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load CardDataTable!"));
        this->SetVisibility(ESlateVisibility::Hidden);
        return;
    }
    UEnum* EnumPtr = StaticEnum<EMode>();
    if (EnumPtr)
    {
        int32 Value = static_cast<int32>(ModeSelection);
        FText DisplayName = EnumPtr->GetDisplayNameTextByValue(Value);
        // 2. 检查行数据是否存在
        FModeData* DataRef = ModeDataTable->FindRow<FModeData>(FName(*DisplayName.ToString()), "");
        if (!DataRef)
        {
            this->SetVisibility(ESlateVisibility::Hidden);
            return;
        }
        ModeTitle->SetText(DataRef->ModeTitle);
        ModeIntroduction->SetText(DataRef->ModeIntroduction);
        Picture->SetBrushFromTexture(DataRef->ModePicture);
    }
}

void UModeSelectionOverlay::Click()
{
}

void UModeSelectionOverlay::UnClick()
{
}

void UModeSelectionOverlay::BTNHover()
{
	PlayAnimationForward(HoverAnim);
    Hover->SetVisibility(ESlateVisibility::Visible);
}

void UModeSelectionOverlay::BTNUnHover()
{
	PlayAnimationReverse(HoverAnim);
    Hover->SetVisibility(ESlateVisibility::Hidden);
}
