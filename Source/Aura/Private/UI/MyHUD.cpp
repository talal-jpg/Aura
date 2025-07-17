// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerState.h"
#include "UI/MyUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AMyHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController=NewObject<UOverlayWidgetController>(WCParams.PlayerController,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}
	return OverlayWidgetController;
}

void AMyHUD::InitOverlay(const FWidgetControllerParams& Params )
{
	FWidgetControllerParams WCParams= FWidgetControllerParams(Params);
	OverlayUserWidget=Cast<UMyUserWidget>(CreateWidget<UUserWidget>(Params.PlayerController,OverlayUserWidgetClass));
	if (OverlayUserWidget == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(2,10,FColor::Yellow,"Unable to create OverlayUserWidget");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(2,10,FColor::Yellow,"OverlayUserWidget Created");
	}
	OverlayUserWidget->SetWidgetController(GetOverlayWidgetController(WCParams));
	OverlayUserWidget->AddToViewport();
	GetOverlayWidgetController(WCParams)->BroadcastInitialValues();
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
}

