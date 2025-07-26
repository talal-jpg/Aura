// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */

struct FMyGameplayTags
{
	public:
	static FMyGameplayTags& Get(){return GameplayTags;};

	static void InitializeGameplayTags();

	// VitalAttributes
	FGameplayTag Attribute_Vital_Health;
	FGameplayTag Attribute_Vital_Mana;
	FGameplayTag Attribute_Vital_MaxHealth;
	FGameplayTag Attribute_Vital_MaxMana;

	// PrimaryAttributes
	FGameplayTag Attribute_Primary_Strength;
	FGameplayTag Attribute_Primary_Intelligence;
	FGameplayTag Attribute_Primary_Resilience;
	FGameplayTag Attribute_Primary_Vigor;

	// SecondaryAttributes
	FGameplayTag Attribute_Secondary_Armor;
	FGameplayTag Attribute_Secondary_ArmorPenetration;
	FGameplayTag Attribute_Secondary_BlockChance;
	FGameplayTag Attribute_Secondary_CriticalHitChance;
	FGameplayTag Attribute_Secondary_CriticalHitDamage;
	FGameplayTag Attribute_Secondary_CriticalHitResistance;
	FGameplayTag Attribute_Secondary_HealthRegeneration;
	FGameplayTag Attribute_Secondary_ManaRegeneration;



	
	FGameplayTag Input_LMB;

	FGameplayTag Message_HealthPotion;
	FGameplayTag Message_ManaPotion;
	FGameplayTag Message_Fire;
	

	private:
	protected:
	static FMyGameplayTags GameplayTags;
};