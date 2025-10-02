// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "GAS/MyAbilitySystemComponent.h"
#include "GAS/MyAttributeSet.h"
#include "GAS/Data/DA_AttributeInfo.h"
#include "Kismet/KismetSystemLibrary.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	UKismetSystemLibrary::PrintString(this,"HelloFromTheOtherSide");

	UMyAttributeSet* MyAttributeSet= Cast<UMyAttributeSet>(AttributeSet);
	if(!MyAttributeSet)
	{
		UE_LOG(LogTemp,Warning,TEXT("AttributeSet: No attribute set."));
		return;
	}
	
		UE_LOG(LogTemp,Warning,TEXT("MyAttributeSetFound"));
	TMap<FGameplayTag,FGameplayAttribute>& Map=MyAttributeSet->AttributeToGameplayTagMap;
	for (auto Pair : Map)
	{
		FAttributeInfo AttributeInfo=DA_AttributeInfo->FindInfoForTag(Pair.Key);
		
		// UKismetSystemLibrary::PrintString(this,AttributeInfo.AttributeName.ToString());
		AttributeInfo.AttributeValue=Pair.Value.GetNumericValue(MyAttributeSet);
		OnAttributeChangeBroadcastAttributeInfoDelegate.Broadcast(AttributeInfo);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
	UMyAttributeSet* MyAttributeSet= Cast<UMyAttributeSet>(AttributeSet);
	if(!MyAttributeSet)
	{
		UE_LOG(LogTemp,Warning,TEXT("AttributeSet: No attribute set."));
		return;
	}
	TMap<FGameplayTag,FGameplayAttribute>& Map=MyAttributeSet->AttributeToGameplayTagMap;
	for (auto Pair : Map)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				FAttributeInfo AttribInfo = DA_AttributeInfo->FindInfoForTag(Pair.Key);
				AttribInfo.AttributeValue=Pair.Value.GetNumericValue(AttributeSet);
				OnAttributeChangeBroadcastAttributeInfoDelegate.Broadcast(AttribInfo);
			}
		);
	}
	
}
