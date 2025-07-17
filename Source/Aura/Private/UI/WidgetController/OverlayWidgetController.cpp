// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/MyAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChangeDelegate.Broadcast(GetMyAttributeSet()->GetHealth());
	OnMaxHealthChangeDelegate.Broadcast(GetMyAttributeSet()->GetMaxHealth());
	OnManaChangeDelegate.Broadcast(GetMyAttributeSet()->GetMana());
	OnMaxManaChangeDelegate.Broadcast(GetMyAttributeSet()->GetMaxMana());
}

UMyAttributeSet* UOverlayWidgetController::GetMyAttributeSet()
{
	if (!MyAttributeSet)
	{
		MyAttributeSet=Cast<UMyAttributeSet>(AttributeSet);
	}
	return MyAttributeSet;
}
