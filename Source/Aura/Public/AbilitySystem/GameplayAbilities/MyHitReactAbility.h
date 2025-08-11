// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbilities/MyGameplayAbility.h"
#include "MyHitReactAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMyHitReactAbility : public UMyGameplayAbility
{
	GENERATED_BODY()

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> HitReactEffectClass;
	
};
