// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/MyAbilitySystemComponent.h"

#include "GAS/GameplayAbility/MyGameplayAbility.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UMyAbilitySystemComponent::UMyAbilitySystemComponent()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&ThisClass::Client_OnGameplayEffectAppliedCallback);
}

void UMyAbilitySystemComponent::AddStartupAbilities(TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for(auto Ability:Abilities)
	{
		FGameplayAbilitySpec AbilitySpec=BuildAbilitySpecFromClass(Ability);
		FGameplayTag StartupInputTag=Cast<UMyGameplayAbility>(AbilitySpec.Ability)->StartupInputTag;
		
		AbilitySpec.DynamicAbilityTags.AddTag(StartupInputTag);
		FGameplayAbilitySpecHandle AbilitySpecHandle=GiveAbility(AbilitySpec);
	}
	bStartupAbilitiesGiven = true;
	OnAbilitiesGivenDelegate.Broadcast(this);
}

void UMyAbilitySystemComponent::ForEachAbility(FOnAbilitiesGivenLoopAllAndBroadcastSpecDelegateSignature& OnAbilitiesGivenLoopAllAndBroadcastSpecDelegate)
{
	FScopedAbilityListLock ScopedLock(*this);
	for (auto Ability:GetActivatableAbilities())
	{
		OnAbilitiesGivenLoopAllAndBroadcastSpecDelegate.ExecuteIfBound(Ability);
	}
}

FGameplayTag UMyAbilitySystemComponent::FindAbilityTagFromSpec(FGameplayAbilitySpec AbilitySpec,FGameplayTag AbilityTag)
{
	for (auto Tag:AbilitySpec.Ability->GetAssetTags())
	{
		if (Tag.MatchesTag(AbilityTag))
		{
			return Tag;
		}
	}
	return FGameplayTag();
}

FGameplayTag UMyAbilitySystemComponent::FindInputTagFromSpec(FGameplayAbilitySpec AbilitySpec, FGameplayTag InputTag)
{
	for (auto Tag: AbilitySpec.GetDynamicSpecSourceTags())
	{
		if (Tag.MatchesTag(InputTag))
		{
			return Tag;
		}
	}
	return FGameplayTag();
}


void UMyAbilitySystemComponent::Client_OnGameplayEffectAppliedCallback_Implementation(UAbilitySystemComponent* ASC,
                                                                                      const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle ActiveGEHandle)
{
	FGameplayTagContainer TagContainer;
	GESpec.GetAllAssetTags(TagContainer);
	// for (auto Tag : TagContainer)
	// {
	// 	UKismetSystemLibrary::PrintString(this,Tag.ToString());
	// }
	OnGameplayEffectAppliedBroadcastAssetTagsDelegate.Broadcast(TagContainer);
}

