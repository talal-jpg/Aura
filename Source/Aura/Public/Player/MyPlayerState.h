// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURA_API AMyPlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
	public:
	AMyPlayerState();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MyPlayerState")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MyPlayerState")
	UAttributeSet* AttributeSet;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
};
