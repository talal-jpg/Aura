// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAssetManager.h"

#include "AbilitySystem/MyGameplayTags.h"
#include "GameFramework/GameSession.h"
#include "Kismet/KismetSystemLibrary.h"

UMyAssetManager& UMyAssetManager::Get()
{
	return *Cast<UMyAssetManager>(GEngine->AssetManager);
}

void UMyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FMyGameplayTags::InitializeGameplayTags();

}

