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
		OverlayWidgetController=NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}
	return OverlayWidgetController;
}

void AMyHUD::InitOverlay(const FWidgetControllerParams& Params )
{
	OverlayUserWidget=Cast<UMyUserWidget>(CreateWidget<UUserWidget>(GetWorld(),OverlayUserWidgetClass));
	APlayerController* PC = GetOwningPlayerController();
	AMyPlayerState* PS= PC->GetPlayerState<AMyPlayerState>();
	UAbilitySystemComponent* ASC=PS->AbilitySystemComponent;
	UAttributeSet* AS= PS->AttributeSet;
	FWidgetControllerParams WCParams= FWidgetControllerParams(PC,PS,ASC,AS);
	OverlayUserWidget->SetWidgetController(GetOverlayWidgetController(WCParams));
	OverlayUserWidget->AddToViewport();
}

