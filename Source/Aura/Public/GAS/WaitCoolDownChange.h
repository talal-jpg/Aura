// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "WaitCoolDownChange.generated.h"

struct FActiveGameplayEffectHandle;
struct FGameplayEffectSpec;
struct FGameplayTag;
class UAbilitySystemComponent;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagChangeBroadcastRemainingTimeDelegateSignature,float ,RemainingTime);

UCLASS()
class AURA_API UWaitCoolDownChange : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"))
	static UWaitCoolDownChange* WaitCoolDownChange(UAbilitySystemComponent* ASC,const FGameplayTag& InCoolDownTag);

	UPROPERTY(BlueprintAssignable)
	FOnTagChangeBroadcastRemainingTimeDelegateSignature CoolDownStart;

	UPROPERTY(BlueprintAssignable)
	FOnTagChangeBroadcastRemainingTimeDelegateSignature CoolDownEnd;
	
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
	
	FGameplayTag CoolDownTag;

	void CoolDownTagChanged(const FGameplayTag InCoolDownTag, int32 NewCount);

	void OnActiveEffectAdded(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle GEHandle);

	void EndTask();
	
};
