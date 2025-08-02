// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AT_GetLocationUnderCursor2.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetDataSetBroadcastLocationDelegateSignature,const FGameplayAbilityTargetDataHandle&, AbilityTargetDataHandle);
/**
 * 
 */
UCLASS()
class AURA_API UAT_GetLocationUnderCursor2 : public UAbilityTask
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintCallable)
	static UAT_GetLocationUnderCursor2* TaskInstance(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FOnTargetDataSetBroadcastLocationDelegateSignature OnTargetDataSetBroadcastLocation;

	virtual void Activate() override;

	void TargetDataSetDelegateCallback(const FGameplayAbilityTargetDataHandle& AbilityTargetDataHandle, FGameplayTag GameplayTag);
	
};
