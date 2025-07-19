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

	FGameplayTag Input_LMB;

	FGameplayTag Message_HealthPotion;
	FGameplayTag Message_ManaPotion;
	FGameplayTag Message_Fire;
	

	private:
	protected:
	static FMyGameplayTags GameplayTags;
};