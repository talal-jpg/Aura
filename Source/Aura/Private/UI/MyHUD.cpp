// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyHUD.h"
#include "Blueprint/UserWidget.h"
#include "Player/MyPlayerState.h"
#include "UI/MyUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void AMyHUD::InitOverlay()
{
	OverlayWidgetController=NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
	APlayerController* PC = GetOwningPlayerController();
	OverlayUserWidget=Cast<UMyUserWidget>(CreateWidget<UUserWidget>(PC,OverlayUserWidgetClass));
	AMyPlayerState* PS = PC->GetPlayerState<AMyPlayerState>();
	UAbilitySystemComponent* ASC= PS->AbilitySystemComponent;
	UAttributeSet* AS= PS->AttributeSet;
	FWidgetControllerParams WCParams= FWidgetControllerParams(PC,PS,ASC,AS);
	OverlayWidgetController->SetWidgetControllerParams(WCParams);
	OverlayUserWidget->SetWidgetController(OverlayWidgetController);
	OverlayWidgetController->BindCallbacksToDependencies();
	OverlayWidgetController->BroadcastInitialValues();
	OverlayUserWidget->AddToViewport();
}

UAttributeMenuWidgetController* AMyHUD::GetAttributeMenuWidgetController() const
{
	if (!AttributeMenuWidgetController)
	{
		AttributeMenuWidgetController=NewObject<UAttributeMenuWidgetController>(GetOwningPlayerController(),AttributeMenuWidgetControllerClass);
	}
	return AttributeMenuWidgetController;
}
