// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MyAbilitySystemComponent.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameplayEffectApplliedBroadcastAssetTagsDelegateSignature,FGameplayTagContainer GEAssetTags);
UCLASS()
class AURA_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	public:
	UMyAbilitySystemComponent();

	FOnGameplayEffectApplliedBroadcastAssetTagsDelegateSignature OnGameplayEffectAppliedBroadcastAssetTagsDelegate;

	UFUNCTION(Client,Reliable)
	void ClientOnEffectAppliedDelegateCallback(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);

	
};
