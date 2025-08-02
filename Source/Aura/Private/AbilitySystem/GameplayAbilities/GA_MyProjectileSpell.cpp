// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbilities/GA_MyProjectileSpell.h"

#include "Quaternion.h"
#include "Actors/MyProjectile.h"
#include "Interface/CombatInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UGA_MyProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void UGA_MyProjectileSpell::SpawnProjectile(const FVector& TargetLocation)
{
	const bool bIsServer=GetAvatarActorFromActorInfo()->HasAuthority();
	if(!bIsServer) return;
	ICombatInterface* CombatInterface= Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (!CombatInterface)return;
	FVector SocketLocation=CombatInterface->GetCombatSocketLocation();
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	FRotator ToTarget= (TargetLocation-SocketLocation).Rotation();
	ToTarget.Pitch=0.0f;
	SpawnTransform.SetRotation(ToTarget.Quaternion());
	
	AMyProjectile* MyProjectile=GetWorld()->SpawnActorDeferred<AMyProjectile>(ProjectileClass,SpawnTransform,GetOwningActorFromActorInfo(),Cast<APawn>(GetOwningActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	UAbilitySystemComponent* SourceAsc=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	FGameplayEffectSpecHandle SpecHandle= SourceAsc->MakeOutgoingSpec(DamageEffectClass,GetAbilityLevel(),SourceAsc->MakeEffectContext());
	MyProjectile->DamageEffectSpecHandle=SpecHandle;
	MyProjectile->FinishSpawning(SpawnTransform);
	
}
