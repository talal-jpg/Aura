// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MyAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/MyGameplayTags.h"
#include "Net/UnrealNetwork.h"

UMyAttributeSet::UMyAttributeSet()
{
	InitHealth(50);
	InitMaxHealth(100);
	InitMana(50);
	InitMaxMana(100);
	
	AttributeGameplayTagMap.Add(FMyGameplayTags::Get().Attribute_Vital_Health,GetHealthAttribute());
	AttributeGameplayTagMap.Add(FMyGameplayTags::Get().Attribute_Vital_MaxHealth,GetMaxHealthAttribute());
	AttributeGameplayTagMap.Add(FMyGameplayTags::Get().Attribute_Vital_Mana,GetManaAttribute());
	AttributeGameplayTagMap.Add(FMyGameplayTags::Get().Attribute_Vital_MaxMana,GetMaxManaAttribute());
	
}

void UMyAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,MaxMana, COND_None, REPNOTIFY_Always);
}

void UMyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,Health,OldValue);
}

void UMyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,MaxHealth,OldValue);
}

void UMyAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,Mana,OldValue);
}

void UMyAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,MaxMana,OldValue);
}

	
