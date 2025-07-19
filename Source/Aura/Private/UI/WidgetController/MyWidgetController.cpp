// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/MyWidgetController.h"

void UMyWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	AbilitySystemComponent=WCParams.AbilitySystemComponent;
	AttributeSet=WCParams.AttributeSet;
	PlayerController=WCParams.PlayerController;
	PlayerState=WCParams.PlayerState;
	WidgetControllerParamsSet();
}

void UMyWidgetController::BroadcastInitialValues()
{
}

void UMyWidgetController::BindCallbackToDependencies()
{
}

