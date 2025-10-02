// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include <string>

#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "GAS/MyAbilitySystemComponent.h"
#include "GAS/MyAttributeSet.h"
#include "GAS/Data/DA_AbilityInfo.h"
#include "Kismet/KismetSystemLibrary.h"

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	// float val= GetMyAttributeSet()->GetHealth();
	// UKismetSystemLibrary::PrintString(this,FString::Printf(TEXT("Healthis%f"),val));
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetMyAttributeSet()->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			float Val=Data.NewValue;
			OnHealthChangeBroadcastValDelegate.Broadcast(Val);
		}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetMyAttributeSet()->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{

			float Val=Data.NewValue;
			OnMaxHealthChangeBroadcastValDelegate.Broadcast(Val);
		}

	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetMyAttributeSet()->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			float Val=Data.NewValue;
			OnManaChangeBroadcastValDelegate.Broadcast(Val);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetMyAttributeSet()->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			float Val=Data.NewValue;
			OnMaxManaChangeBroadcastValDelegate.Broadcast(Val);
		}
	);
	
	// AbilitySystemComponent->OnGameplayEffectAppliedDelegateToSelf.AddLambda(
	// 	[this](UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle)
	// 	{
	// 		FGameplayTagContainer TagContainer;
	// 		EffectSpec.GetAllAssetTags(TagContainer);
	// 		for (const FGameplayTag& Tag : TagContainer)
	// 		{
	// 			FPopupWidgetRow* PopupWidgetRow = PopUpWidgetInfo->FindRow<FPopupWidgetRow>(Tag.GetTagName(), FString());
	// 			if (PopupWidgetRow)
	// 			{
	// 				OnEffectAppliedBroadcastPopupWidgetRowDelegate.Broadcast(*PopupWidgetRow);
	// 			}
	// 			else
	// 			{
	// 				UKismetSystemLibrary::PrintString(this,"Didn't find PopupWidgetRow");
	// 			}
	// 		}
	// 	}
	// 	);
	UMyAbilitySystemComponent* MyASC=Cast<UMyAbilitySystemComponent>(AbilitySystemComponent);
	if (MyASC->bStartupAbilitiesGiven)
	{
		OnInitializeStartupAbilities(MyASC);
	}
	else
	{
		MyASC->OnAbilitiesGivenDelegate.AddUObject(this,&UOverlayWidgetController::OnInitializeStartupAbilities);
	}

	MyASC->OnGameplayEffectAppliedBroadcastAssetTagsDelegate.AddLambda(
		[this](FGameplayTagContainer& TagContainer)
		{

			float Health=GetMyAttributeSet()->GetHealth();
			for (const FGameplayTag& Tag : TagContainer)
			{
				FPopupWidgetRow* PopupWidgetRow = PopUpWidgetInfo->FindRow<FPopupWidgetRow>(Tag.GetTagName(), FString(""));
				if (PopupWidgetRow)
				{
					OnEffectAppliedBroadcastPopupWidgetRowDelegate.Broadcast(*PopupWidgetRow);
				}
				else
				{
					UKismetSystemLibrary::PrintString(this,"PopupWidgetRowNotFound");
				}
				
			}
		}
	);

}

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChangeBroadcastValDelegate.Broadcast(GetMyAttributeSet()->GetHealth());
	OnMaxHealthChangeBroadcastValDelegate.Broadcast(GetMyAttributeSet()->GetMaxHealth());
	OnManaChangeBroadcastValDelegate.Broadcast(GetMyAttributeSet()->GetMana());
	OnMaxManaChangeBroadcastValDelegate.Broadcast(GetMyAttributeSet()->GetMaxMana());
}

UMyAttributeSet* UOverlayWidgetController::GetMyAttributeSet()
{
	if (!MyAttributeSet)
	{
		MyAttributeSet = Cast<UMyAttributeSet>(AttributeSet);
	}
	return MyAttributeSet;
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UMyAbilitySystemComponent* AbilitySystemComponent)
{
	if (!AbilitySystemComponent->bStartupAbilitiesGiven)return;

	FOnAbilitiesGivenLoopAllAndBroadcastSpecDelegateSignature OnAbilitiesGivenLoopAllAndBroadcastSpecDelegate;
	OnAbilitiesGivenLoopAllAndBroadcastSpecDelegate.BindLambda(
		[this](FGameplayAbilitySpec AbilitySpec)
		{
			const FGameplayTag& AbilityTag=UMyAbilitySystemComponent::FindAbilityTagFromSpec(AbilitySpec,UGameplayTagsManager::Get().RequestGameplayTag(FName("Ability")));
			FAbilityInfo AbilityInfo=DA_AbilityInfo->FindAbilityInfoForTag(AbilityTag,true);
			AbilityInfo.InputTag= UMyAbilitySystemComponent::FindInputTagFromSpec(AbilitySpec,UGameplayTagsManager::Get().RequestGameplayTag(FName("Input")));
			OnAbilitiesGivenBroadcastAbilityInfoDelegate.Broadcast(AbilityInfo);
		}
		);
	
	Cast<UMyAbilitySystemComponent>(AbilitySystemComponent)->ForEachAbility(OnAbilitiesGivenLoopAllAndBroadcastSpecDelegate);
	
}
