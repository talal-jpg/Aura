// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/MyAttributeSet.h"

#include <string>

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameplayTagsManager.h"
#include "MyGameModeBase.h"
#include "AbilitySystem/MyGameplayTags.h"
#include "Character/CharacterBase.h"
#include "Character/CharacterEnemy.h"
#include "Interface/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

UMyAttributeSet::UMyAttributeSet()
{

	/**
	 *dont register if hot reload
	 */
	
	// AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Vital.Health")),GetHealthAttribute());
	// AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Vital.Mana")),GetManaAttribute());
	
	// AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Primary.Strength")),GetStrengthAttribute());
	// AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Primary.Intelligence")),GetIntelligenceAttribute());
	// AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Primary.Resilience")),GetResilienceAttribute());
	// AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Primary.Vigor")),GetVigorAttribute());
	
	AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Primary.Intelligence")),GetIntelligenceAttribute());
	AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Primary.Strength")),GetStrengthAttribute());
	AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Primary.Resilience")),GetResilienceAttribute());
	AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Primary.Vigor")),GetVigorAttribute());
	
	AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.Armor")),GetArmorAttribute());
	AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.ArmorPenetration")),GetArmorPenetrationAttribute());
	AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.BlockChance")),GetBlockChanceAttribute());
	AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.CriticalHitChance")),GetCriticalHitChanceAttribute());
	AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.CriticalHitDamage")),GetCriticalHitDamageAttribute());
	AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.CriticalHitResistance")),GetCriticalHitResistanceAttribute());
	AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.HealthRegeneration")),GetHealthRegenerationAttribute());
	AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Secondary.ManaRegeneration")),GetManaRegenerationAttribute());
	AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Vital.MaxHealth")),GetMaxHealthAttribute());
	AttributeToGameplayTagMap.Add(UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Vital.MaxMana")),GetMaxManaAttribute());
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

void UMyAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	if (Attribute== GetHealthAttribute())
	{
		NewValue= FMath::Clamp(NewValue,0,GetMaxHealth());
	}
}

void UMyAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute==GetHealthAttribute())
	{
		SetHealth( FMath::Clamp(GetHealth(),0,GetMaxHealth()));
	}
	
	if (Data.EvaluatedData.Attribute==GetIncomingDamageAttribute())
	{
		float LocalIncomingDamage= GetIncomingDamage();
		SetIncomingDamage(0);
		if (LocalIncomingDamage>0)
		{
			const float NewHealth= GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth,0,GetMaxHealth()));
	
			const bool bFatal = NewHealth<= 0;
			if (!bFatal)
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag(FName("Effects.HitReact")));
				AActor* TargetAvatarActor=Data.Target.GetAvatarActor();
				UAbilitySystemComponent* TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetAvatarActor);
				TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}
	
			if (bFatal)
			{
				ICombatInterface* CombatInterface=Cast<ICombatInterface>(Data.Target.GetAvatarActor());
				if (CombatInterface)
				{
					CombatInterface->Die();
				}

				AMyGameModeBase* MyGameMOdeBase=Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(Data.Target.GetAvatarActor()));
				UDA_DefaultEnemyAttributes* DefaultEnemyAttribs=MyGameMOdeBase->DefaultEnemyAttributesInfo;
				ECharacterClass CharacterClass=Cast<ACharacterEnemy>(Data.Target.GetAvatarActor())->CharacterClass;
				float Xp=DefaultEnemyAttribs->GetCharacterClassInfo(CharacterClass)->XpGiven.GetValueAtLevel(1);
				FGameplayEventData EventData;
				EventData.EventMagnitude=Xp;
				
				AActor* Instigator=Data.EffectSpec.GetContext().GetInstigator();
				
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Instigator,UGameplayTagsManager::Get().RequestGameplayTag(FName("Event.XpGiven")),EventData);
				
			}
		}
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

	
