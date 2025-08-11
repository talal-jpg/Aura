// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbilities/MyGameplayAbility.h"
#include "GA_MyProjectileSpell.generated.h"

class AMyProjectile;
/**
 * 
 */
UCLASS()
class AURA_API UGA_MyProjectileSpell : public UMyGameplayAbility
{
	GENERATED_BODY()
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& TargetLocation);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMyProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> HitReactEffectClass;
	

	UPROPERTY(EditAnywhere)
	FScalableFloat ProjectileDamage;
};
