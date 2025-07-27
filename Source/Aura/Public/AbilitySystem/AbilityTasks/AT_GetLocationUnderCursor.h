// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AT_GetLocationUnderCursor.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetLocationUnderCursorDelegateSignature, const FGameplayAbilityTargetDataHandle&,TargetDataHandle);

UCLASS()
class AURA_API UAT_GetLocationUnderCursor : public UAbilityTask
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	static UAT_GetLocationUnderCursor* AT_GetLocationUnderCursor(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FGetLocationUnderCursorDelegateSignature GetLocationUnderCursorDelegate;
	
	virtual void Activate() override;

	void SendMouseCursorData();
	
	void TargetDataDelegateCallBack(const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag GameplayTag);
};
