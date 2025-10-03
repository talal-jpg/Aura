// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MyAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMyAssetManager : public UAssetManager
{
	GENERATED_BODY()

	static UMyAssetManager& Get();
	
	virtual void StartInitialLoading() override;

};
