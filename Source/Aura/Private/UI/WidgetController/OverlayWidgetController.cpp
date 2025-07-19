// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "AbilitySystem/MyGameplayTags.h"
#include "Kismet/KismetSystemLibrary.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChangeDelegate.Broadcast(GetMyAttributeSet()->GetHealth());
	OnMaxHealthChangeDelegate.Broadcast(GetMyAttributeSet()->GetMaxHealth());
	OnManaChangeDelegate.Broadcast(GetMyAttributeSet()->GetMana());
	OnMaxManaChangeDelegate.Broadcast(GetMyAttributeSet()->GetMaxMana());
}

void UOverlayWidgetController::BindCallbackToDependencies()
{
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetMyAttributeSet()->GetHealthAttribute()).AddUObject(this,&ThisClass::OnHeathChange);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetMyAttributeSet()->GetMaxHealthAttribute()).AddUObject(this,&ThisClass::OnMaxHealthChange);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetMyAttributeSet()->GetManaAttribute()).AddUObject(this,&ThisClass::OnManaChange);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetMyAttributeSet()->GetMaxManaAttribute()).AddUObject(this,&ThisClass::OnMaxManaChange);

	Cast<UMyAbilitySystemComponent>(AbilitySystemComponent)->OnGameplayEffectAppliedBroadcastAssetTagsDelegate.AddLambda(
		[this](FGameplayTagContainer GEAssetTags)
		{
			for (FGameplayTag AssetTag : GEAssetTags)
			{

				FName RowName= AssetTag.GetTagName();
				FPopUpWidgetInfo* PopUpWidgetInfo=DT_PopUpWidgetInfo->FindRow<FPopUpWidgetInfo>(RowName,TEXT(""));
				OnGameplayEffectAppliedBroadcastPopUpWidgetInfoDelegate.Broadcast(*PopUpWidgetInfo);
			}
		}
	);
}

UMyAttributeSet* UOverlayWidgetController::GetMyAttributeSet()
{
	if (!MyAttributeSet)
	{
		MyAttributeSet=Cast<UMyAttributeSet>(AttributeSet);
	}
	return MyAttributeSet;
}

void UOverlayWidgetController::OnHeathChange(const FOnAttributeChangeData& HealthData)
{

	float NewHealth=HealthData.NewValue;
	OnHealthChangeDelegate.Broadcast(NewHealth);
}

void UOverlayWidgetController::OnMaxHealthChange(const FOnAttributeChangeData& MaxHealthData)
{
	float NewMaxHealth=MaxHealthData.NewValue;
	OnMaxHealthChangeDelegate.Broadcast(NewMaxHealth);
}

void UOverlayWidgetController::OnManaChange(const FOnAttributeChangeData& ManaData)
{
	float NewMana=ManaData.NewValue;
	OnManaChangeDelegate.Broadcast(NewMana);
}

void UOverlayWidgetController::OnMaxManaChange(const FOnAttributeChangeData& MaxManaData)
{
	float NewMaxMana=MaxManaData.NewValue;
	OnMaxManaChangeDelegate.Broadcast(NewMaxMana);
}

