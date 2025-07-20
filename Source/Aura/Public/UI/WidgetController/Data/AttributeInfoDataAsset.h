// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfoDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FAttributeInfoStruct 
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FGameplayTag AttributeGameplayTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText AttributeName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText AttributeDescription;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AttributeValue;
};
/**
 * 
 */
UCLASS()
class AURA_API UAttributeInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
	public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FAttributeInfoStruct> AttributeInfo;
	
};
