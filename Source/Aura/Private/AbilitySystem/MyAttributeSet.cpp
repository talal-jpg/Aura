// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MyAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

UMyAttributeSet::UMyAttributeSet()
{

	/**
	 *dont register if hot reload
	 */
//	AttributeGameplayTagMap.Add(FMyGameplayTags::Get().Attribute_Vital_Health,GetHealthAttribute());
//	AttributeGameplayTagMap.Add(FMyGameplayTags::Get().Attribute_Vital_MaxHealth,GetMaxHealthAttribute());
//	AttributeGameplayTagMap.Add(FMyGameplayTags::Get().Attribute_Vital_Mana,GetManaAttribute());
//	AttributeGameplayTagMap.Add(FMyGameplayTags::Get().Attribute_Vital_MaxMana,GetMaxManaAttribute());
	
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Vital.Health")),GetHealthAttribute());
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Vital.Mana")),GetManaAttribute());
	//
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Primary.Strength")),GetStrengthAttribute());
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Primary.Intelligence")),GetIntelligenceAttribute());
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Primary.Resilience")),GetResilienceAttribute());
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Primary.Vigor")),GetVigorAttribute());
	//
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.Armor")),GetArmorAttribute());
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.ArmorPenetration")),GetArmorPenetrationAttribute());
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.BlockChance")),GetBlockChanceAttribute());
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.CriticalHitChance")),GetCriticalHitChanceAttribute());
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.CriticalHitDamage")),GetCriticalHitDamageAttribute());
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.CriticalHitResistance")),GetCriticalHitResistanceAttribute());
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.HealthRegeneration")),GetHealthRegenerationAttribute());
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.ManaRegeneration")),GetManaRegenerationAttribute());
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Vital.MaxHealth")),GetMaxHealthAttribute());
	// AttributeGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Vital.MaxMana")),GetMaxManaAttribute());
}

void UMyAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Mana, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Vigor, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,MaxMana, COND_None, REPNOTIFY_Always);
	
}

void UMyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute== GetHealthAttribute())
	{
		NewValue= FMath::Clamp(NewValue,0,GetMaxHealth());
	}
	if (Attribute== GetManaAttribute())
	{
		NewValue= FMath::Clamp(NewValue,0,GetMaxMana());
	}
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if(Data.EvaluatedData.Attribute==GetHealthAttribute())
	{
		float Mag=  Data.EvaluatedData.Magnitude;
		SetHealth(FMath::Clamp(GetHealth(),0,GetMaxHealth()));
		// UKismetSystemLibrary::PrintString(this,FString::Printf(TEXT("Health: %f\n"),Mag));
	}
	
	
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

void UMyAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,Strength,OldValue);
}

void UMyAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,Intelligence,OldValue);
}

void UMyAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,Resilience,OldValue);
}

void UMyAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,Vigor,OldValue);
}

void UMyAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldValue) const
{
	
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,Armor,OldValue);
}

void UMyAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,ArmorPenetration,OldValue);
}

void UMyAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,BlockChance,OldValue);
}

void UMyAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,CriticalHitChance,OldValue);
}

void UMyAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,CriticalHitDamage,OldValue);
}

void UMyAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,CriticalHitResistance,OldValue);
}

void UMyAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,HealthRegeneration,OldValue);
}

void UMyAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,ManaRegeneration,OldValue);
}

	
