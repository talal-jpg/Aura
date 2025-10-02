// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScalableFloat.h"
#include "Engine/DataAsset.h"
#include "DA_DefaultEnemyAttributes.generated.h"

struct FScalableFloat;
class UGameplayAbility;
class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass: uint8
{
	Warrior, 
	Ranger, 
	Elementalist 
};

USTRUCT(BlueprintType)
struct FCharacterClassInfo
{
	GENERATED_BODY()
	FCharacterClassInfo(){};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayAbility>> SpecificAbilitiesPerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FScalableFloat XpGiven;
};
/**
 * 
 */
UCLASS()
class AURA_API UDA_DefaultEnemyAttributes : public UDataAsset
{
	GENERATED_BODY()


	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ECharacterClass,FCharacterClassInfo> ClassToInfo;

	FCharacterClassInfo GetInfoFromClass(ECharacterClass ClassToGet);

	UPROPERTY(EditAnywhere, Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
	UPROPERTY(EditAnywhere, Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	FCharacterClassInfo* GetCharacterClassInfo(ECharacterClass InCharacterClass);

	UPROPERTY(EditAnywhere, Category="Common Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;
	
};
