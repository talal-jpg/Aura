// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

enum class ECharacterClass : uint8;
class UAbilitySystemComponent;
class UAttributeMenuWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);


	UFUNCTION(BlueprintCallable)
	static void InitializeDefaultCharacterAttributes(UObject* WorldContextObject,ECharacterClass CharacterClass,float Level,UAbilitySystemComponent* AbilitySystemComponent);
};
