// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DA_InputConfig.generated.h"

class UInputAction;
/**
 * 
 */
USTRUCT()
struct FMyInputConfig
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere)
	FGameplayTag InputTag;

	UPROPERTY(EditAnywhere)
	UInputAction* InputAction;
	
};
UCLASS()
class AURA_API UDA_InputConfig : public UDataAsset
{
	GENERATED_BODY()

	public:
	
	UPROPERTY(EditAnywhere)
	TArray<FMyInputConfig> InputConfigs;

	UInputAction* GetInputActionByTag(const FGameplayTag& InputTag,bool bGiveWarning=false);
	
};
