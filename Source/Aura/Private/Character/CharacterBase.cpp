// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	WeaponMesh=CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetMesh(),FName("HandSocket"));
	bReplicates = true;
}

FVector ACharacterBase::GetCombatSocketLocation()
{
	return WeaponMesh->GetSocketLocation(WeaponTipSocketName);
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACharacterBase::InitializePrimaryAttributes()
{
	ApplyEffect(DefaultPrimaryAttributes);
}

void ACharacterBase::InitializeSecondaryAttributes()
{
	ApplyEffect(DefaultSecondaryAttributes);
}

void ACharacterBase::InitializeVitalAttributes()
{
	ApplyEffect(DefaultVitalAttributes);
}

void ACharacterBase::ApplyEffect(TSubclassOf<UGameplayEffect> EffectClass)
{
	FGameplayEffectContextHandle EffectContextHandle=GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle=GetAbilitySystemComponent()->MakeOutgoingSpec(EffectClass, 1,EffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

int ACharacterBase::GetPlayerLevel()
{
	int PlayerLevel=0;
	return PlayerLevel;
}




