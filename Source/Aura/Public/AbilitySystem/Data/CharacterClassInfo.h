// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass:uint8{
	Warrior,
	Ranger,
	Elementalist
};
USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
};

/**
 * 
 */
UCLASS()
class AURA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere,Category = "Commmon Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
	
	UPROPERTY(EditAnywhere,Category = "Commmon Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	UPROPERTY(EditAnywhere,Category = "Class Defaults")
	TMap<ECharacterClass,FCharacterClassDefaultInfo> CharClassToCharClassInfo;

	
	FCharacterClassDefaultInfo GetCharacterClassDefaultInfo(ECharacterClass CharacterClass);
	
};
