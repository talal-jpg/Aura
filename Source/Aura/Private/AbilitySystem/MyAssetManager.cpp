// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MyAssetManager.h"

#include "AbilitySystem/MyGameplayTags.h"

UMyAssetManager& UMyAssetManager::Get()
{
	return *Cast<UMyAssetManager>(GEngine->AssetManager);
}

void UMyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FMyGameplayTags::Get().InitializeGameplayTags();
}
