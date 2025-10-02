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
struct FInputConfig
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY(EditAnywhere)
	FGameplayTag InputTag;
	
};
UCLASS()
class AURA_API UDA_InputConfig : public UDataAsset
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere)
	TArray<FInputConfig> InputConfigs;

	UInputAction* GetInputActionByInputTag(FGameplayTag& InputTag);

	
	
};
