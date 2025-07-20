// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MyAbilitySystemComponent.h"

#include "AbilitySystem/MyAttributeSet.h"

UMyAbilitySystemComponent::UMyAbilitySystemComponent()
{
	/**
	 *PopUpWidgetDoesntHaveAControllerThatIsWhyWeBroadcastDelegateHere
	 */
	OnGameplayEffectAppliedDelegateToSelf.AddLambda(
		[this](UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
		{
			FGameplayTagContainer AssetTagsOnGEContainer;
			GESpec.GetAllAssetTags(AssetTagsOnGEContainer);
			OnGameplayEffectAppliedBroadcastAssetTagsDelegate.Broadcast(AssetTagsOnGEContainer);
		}
	);
}
