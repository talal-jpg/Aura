// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GA_GetLocationUnderCursor.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickBroadcastTargetDataDelegateSignature,FGameplayAbilityTargetDataHandle, TargetDataHandle);
UCLASS()
class AURA_API UGA_GetLocationUnderCursor : public UAbilityTask
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static UGA_GetLocationUnderCursor* TaskInstance(UGameplayAbility* OwningAbility);
	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FOnClickBroadcastTargetDataDelegateSignature OnClickBroadcastTargetDataDelegate;

	void OnTargetDataSetDelegateCallback(const FGameplayAbilityTargetDataHandle& AbilityTargetDataHandle, FGameplayTag GameplayTag);
};
