// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbilities/MyHitReactAbility.h"

#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UMyHitReactAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	// FGameplayEffectContextHandle EffectContextHandle=ActorInfo->AbilitySystemComponent.Get()->MakeEffectContext();
	// EffectContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	// FGameplayEffectSpecHandle EffectSpecHandle=ActorInfo->AbilitySystemComponent.Get()->MakeOutgoingSpec(HitReactEffectClass,1,EffectContextHandle);
	// ActorInfo->AbilitySystemComponent.Get()->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	// UKismetSystemLibrary::PrintString(this,"HitReacting");
}
