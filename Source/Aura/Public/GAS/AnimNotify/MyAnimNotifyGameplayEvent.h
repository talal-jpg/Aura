// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "MyAnimNotifyGameplayEvent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMyAnimNotifyGameplayEvent : public UAnimNotify
{
	GENERATED_BODY()

	public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag EventTag;
	
};
