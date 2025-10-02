// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MyAbilitySystemComponent.generated.h"

class UMyAbilitySystemComponent;
/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameplayEffectAppliedBroadcastAssetTagsDelegateSignature, FGameplayTagContainer& );
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilitiesGivenDelegateSignature,UMyAbilitySystemComponent*);
DECLARE_DELEGATE_OneParam(FOnAbilitiesGivenLoopAllAndBroadcastSpecDelegateSignature,FGameplayAbilitySpec AbilitySpec);


UCLASS()
class AURA_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	UMyAbilitySystemComponent();


public:
	
	UFUNCTION(Client, Reliable)
	void Client_OnGameplayEffectAppliedCallback(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle ActiveGEHandle);

	void AddStartupAbilities(TArray<TSubclassOf<UGameplayAbility>>& Abilities);
	bool bStartupAbilitiesGiven = false;
	
	FOnGameplayEffectAppliedBroadcastAssetTagsDelegateSignature OnGameplayEffectAppliedBroadcastAssetTagsDelegate;
	FOnAbilitiesGivenDelegateSignature OnAbilitiesGivenDelegate;

	void ForEachAbility(FOnAbilitiesGivenLoopAllAndBroadcastSpecDelegateSignature& OnAbilitiesGivenLoopAllAndBroadcastSpecDelegate);

	static FGameplayTag FindAbilityTagFromSpec(FGameplayAbilitySpec AbilitySpec,FGameplayTag AbilityTag);

	static FGameplayTag FindInputTagFromSpec(FGameplayAbilitySpec AbilitySpec,FGameplayTag InputTag);
};
