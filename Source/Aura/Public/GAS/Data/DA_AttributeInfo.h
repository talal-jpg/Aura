// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DA_AttributeInfo.generated.h"

USTRUCT(BlueprintType,Blueprintable)
struct FAttributeInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGameplayTag AttributeTag=FGameplayTag();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText AttributeName=FText();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText  AttributeDescription=FText();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AttributeValue=0;
};
/**
 * 
 */
UCLASS()
class AURA_API UDA_AttributeInfo : public UDataAsset
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FAttributeInfo> AttributeInfoArray;

	FAttributeInfo FindInfoForTag(FGameplayTag AttributeTag);
	
};
