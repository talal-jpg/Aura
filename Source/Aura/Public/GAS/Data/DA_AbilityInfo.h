// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameplayTagContainer.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_AbilityInfo.generated.h"

USTRUCT(BlueprintType,Blueprintable)
struct FAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGameplayTag AbilityTag;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGameplayTag InputTag;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* Icon=nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMaterialInterface* BackgroundMaterial=nullptr;
	
};


/**
 * 
 */
UCLASS()
class AURA_API UDA_AbilityInfo : public UDataAsset
{
	GENERATED_BODY()

	public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FAbilityInfo> AbilitiesInfo;

	FAbilityInfo FindAbilityInfoForTag(const FGameplayTag& AbilityTag,bool bLogResult) const;
	
};
