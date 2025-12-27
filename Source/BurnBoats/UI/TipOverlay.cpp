// Fill out your copyright notice in the Description page of Project Settings.


#include "TipOverlay.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


void UTipOverlay::NativePreConstruct()
{
	Super::NativePreConstruct();
	BTN->OnClicked.AddDynamic(this, &UTipOverlay::BTNPressed);
	BTN->OnHovered.AddDynamic(this, &UTipOverlay::BTN1Hover);
	BTN->OnUnhovered.AddDynamic(this, &UTipOverlay::BTN1UnHover);
}

void UTipOverlay::BTNPressed()
{
	RemoveFromParent();
}

void UTipOverlay::BTN1Hover()
{
	if (T1) T1->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UTipOverlay::BTN1UnHover()
{
	if (T1) T1->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f));
}

void UTipOverlay::Update(FString TitleText, FString MSGText)
{
	Title->SetText(FText::FromString(TitleText));
	MSG->SetText(FText::FromString(MSGText));
}
