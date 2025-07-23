// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include <string>

#include "AbilitySystem/MyAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/WidgetController/Data/AttributeInfoDataAsset.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	UMyAttributeSet* MyAttributeSet= Cast<UMyAttributeSet>(AttributeSet);
	for (auto Pair:Cast<UMyAttributeSet>(AttributeSet)->AttributeGameplayTagMap)
	{
		float Value=Pair.Value.GetNumericValue(MyAttributeSet);
		FAttributeInfoStruct AttributeInfo=DA_AttributeInfo->GetAttributeInfoByTag(Pair.Key);
		AttributeInfo.AttributeValue=Value;
		//UKismetSystemLibrary::PrintString(this,AttributeInfo.AttributeDescription.ToString(),true,false,FLinearColor::Red,10);
		OnAttributeChangeBroadcastAttributeInfoDelegate.Broadcast(AttributeInfo);
	}
}
