// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MyGameplayTags.h"

#include "GameplayTagsManager.h"


FMyGameplayTags FMyGameplayTags::GameplayTags;

void FMyGameplayTags::InitializeGameplayTags()
{
	GameplayTags.Input_LMB=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.LMB"));
}
