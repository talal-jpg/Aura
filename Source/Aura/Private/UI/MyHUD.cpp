// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerState.h"
#include "UI/MyUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
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

UAttributeMenuWidgetController* AMyHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController== nullptr)
	{
		AttributeMenuWidgetController=NewObject<UAttributeMenuWidgetController>(WCParams.PlayerController,AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
	}
	return AttributeMenuWidgetController;
}

void AMyHUD::InitOverlay(const FWidgetControllerParams& Params )
{
	FWidgetControllerParams WCParams= FWidgetControllerParams(Params);
	OverlayUserWidget=Cast<UMyUserWidget>(CreateWidget<UUserWidget>(Params.PlayerController,OverlayUserWidgetClass));ImageParallelForComputeNumJobsForPixels()
	OverlayUserWidget->SetWidgetController(GetOverlayWidgetController(WCParams));
	OverlayUserWidget->AddToViewport();
	GetOverlayWidgetController(WCParams)->BroadcastInitialValues();
	GetOverlayWidgetController(WCParams)->BindCallbackToDependencies();
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
}

