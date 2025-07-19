// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MyGameplayTags.h"

#include "GameplayTagsManager.h"


FMyGameplayTags FMyGameplayTags::GameplayTags;

void FMyGameplayTags::InitializeGameplayTags()
{
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
}
