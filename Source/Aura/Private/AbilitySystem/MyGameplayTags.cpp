// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MyGameplayTags.h"

#include "GameplayTagsManager.h"


FMyGameplayTags FMyGameplayTags::GameplayTags;

void FMyGameplayTags::InitializeGameplayTags()
{
	/**
	 *AttributeTags
	 */
	GameplayTags.Attribute_Vital_Health=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"),FString("HealthAttribute"));
	GameplayTags.Attribute_Vital_MaxHealth=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxHealth"),FString("MaxHealthAttribute"));
	GameplayTags.Attribute_Vital_Mana=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"),FString("ManaAttribute"));
	GameplayTags.Attribute_Vital_Mana= UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Vital.Mana"));
	GameplayTags.Attribute_Vital_MaxMana=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxMana"),FString("MaxManaAttribute"));
	GameplayTags.Attribute_Vital_MaxMana= UGameplayTagsManager::Get().RequestGameplayTag(FName("Attributes.Vital.MaxMana"));


	/**
	 *PrimaryAttributesTags
	 */
	GameplayTags.Attribute_Primary_Strength=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"),FString("PrimaryAttributeStrength"));
	GameplayTags.Attribute_Primary_Intelligence=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"),FString("PrimaryAttributeIntelligence"));
	GameplayTags.Attribute_Primary_Resilience=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"),FString("PrimaryAttributeResilience"));
	GameplayTags.Attribute_Primary_Vigor=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"),FString("PrimaryAttributeVigor"));

	/**
	 *SecondaryAttributesTags
	 */
	GameplayTags.Attribute_Secondary_Armor=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),FString("Attribute_Secondary_Armor"));
	GameplayTags.Attribute_Secondary_ArmorPenetration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"),FString("Attribute_Secondary_ArmorPenetration"));
	GameplayTags.Attribute_Secondary_BlockChance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"),FString("Attribute_Secondary_BlockChance"));
	GameplayTags.Attribute_Secondary_CriticalHitChance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"),FString("Attribute_Secondary_CriticalHitChance"));
	GameplayTags.Attribute_Secondary_CriticalHitDamage=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"),FString("Attribute_Secondary_CriticalHitDamage"));
	GameplayTags.Attribute_Secondary_CriticalHitResistance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"),FString("Attribute_Secondary_CriticalHitResistance"));
	GameplayTags.Attribute_Secondary_HealthRegeneration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"),FString("Attribute_Secondary_HealthRegeneration"));
	GameplayTags.Attribute_Secondary_ManaRegeneration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"),FString("Attribute_Secondary_ManaRegeneration"));
	
	
	/**
	 *InputTags
	 */
	GameplayTags.Input_LMB=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.LMB"),FString("Input left mouse button"));


	/**
	 *MessageTags
	 */
	GameplayTags.Message_HealthPotion=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthPotion"),FString("Health Potion"));
	GameplayTags.Message_ManaPotion=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaPotion"),FString("Mana Potion"));
	GameplayTags.Message_Fire=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.Fire"),FString("Fire"));

	/**
	 *MetaAttributesTags
	 */
	GameplayTags.Damage=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"),FString("Damage"));

	
	GameplayTags.Effects_HitReact=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"),FString("Effects_HitReact"));
	
	UGameplayTagsManager::Get().DoneAddingNativeTags();
}
