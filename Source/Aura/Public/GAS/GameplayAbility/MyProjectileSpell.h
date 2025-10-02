// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GameplayAbility/MyGameplayAbility.h"
#include "MyProjectileSpell.generated.h"

class AMyProjectile;
/**
 * 
 */
UCLASS()
class AURA_API UMyProjectileSpell : public UMyGameplayAbility
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(FVector TargetLocation);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMyProjectile> ProjectileClass;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> DamageGEClass;

	
};
