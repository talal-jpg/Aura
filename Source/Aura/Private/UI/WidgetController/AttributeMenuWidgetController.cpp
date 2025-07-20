// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/MyAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	for (auto Pair:Cast<UMyAttributeSet>(AttributeSet)->AttributeGameplayTagMap)
	{
		FString String=Pair.Key.GetTagName().ToString();
		UKismetSystemLibrary::PrintString(this,String);
	}
}
