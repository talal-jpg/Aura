// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GameplayAbility/MyProjectileSpell.h"

#include <string>

#include "AbilitySystemInterface.h"
#include "Actors/MyProjectile.h"
#include "Interface/CombatInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "MyAbilityTypes.h"
#include "GAS/MyBlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UMyProjectileSpell::SpawnProjectile(FVector TargetLocation)
{
	FTransform SpawnTransform;
	
	// SpawnTransform.SetRotation(FQuat(TargetLocation.Rotation()));
	ICombatInterface* CombatInterface=Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	FVector SocketLocation=CombatInterface->GetSocketLocation_Implementation(FName("TipSocket"));
	
	SpawnTransform.SetLocation(SocketLocation);
	FVector ToTarget=(TargetLocation-SocketLocation).GetSafeNormal();
	UE::Math::TQuat<double> Quat = ToTarget.ToOrientationQuat();
	SpawnTransform.SetRotation(Quat);
	
	AMyProjectile* MyProjectile=GetWorld()->SpawnActorDeferred<AMyProjectile>(ProjectileClass,SpawnTransform);
	UAbilitySystemComponent* SourceASC= UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	FGameplayEffectContextHandle ContextHandle=SourceASC->MakeEffectContext();
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(),MyProjectile);
	ContextHandle.AddSourceObject(MyProjectile);
	
	FGameplayEffectSpecHandle DamageGESpecHandle=SourceASC->MakeOutgoingSpec(DamageGEClass,1,ContextHandle);
	// UAbilitySystemBlueprintLibrary::AssignSetByCallerMagnitude(DamageGESpecHandle,FName("Damage"),10);
	FGameplayTag DamageTag= UGameplayTagsManager::Get().RequestGameplayTag(FName("Damage"));
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageGESpecHandle,DamageTag,DamageCurve.GetValueAtLevel(3));
	MyProjectile->DamageGESpec=*DamageGESpecHandle.Data.Get();
	MyProjectile->FinishSpawning(SpawnTransform);
	
	// UMyBlueprintFunctionLibrary::SetIsBlockedHit(ContextHandle,true);
	// UKismetSystemLibrary::PrintString(this,FString::FromInt(UMyBlueprintFunctionLibrary::IsBlockedHit(ContextHandle)));
}

void UMyProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}
