// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GetHitResultUnderCursorData.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetUnderCursorDataDelegateSignature, FVector, HitLoc);
/**
 * 
 */
UCLASS()
class AURA_API UGetHitResultUnderCursorData : public UAbilityTask
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintCallable)
	static UGetHitResultUnderCursorData* GetHitResultUnderCursor(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FMouseTargetUnderCursorDataDelegateSignature GetMouseTargetUnderCursorDataDelegate;

	virtual void Activate() override;
	
};
