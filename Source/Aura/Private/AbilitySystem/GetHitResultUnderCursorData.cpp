// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GetHitResultUnderCursorData.h"

UGetHitResultUnderCursorData* UGetHitResultUnderCursorData::GetHitResultUnderCursor(UGameplayAbility* OwningAbility)
{
	// Ability
	UGetHitResultUnderCursorData* MyObj= NewAbilityTask<UGetHitResultUnderCursorData>(OwningAbility);
	return MyObj;
}

void UGetHitResultUnderCursorData::Activate()
{
	Super::Activate();
	FVector Location=FVector::ZeroVector;
	GetMouseTargetUnderCursorDataDelegate.Broadcast(FVector(1,0,0));
}
