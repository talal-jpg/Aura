// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/MyWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UMyAttributeSet;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeDelegateSignature, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangeDelegateSignature, float, MaxHealth );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangeDelegateSignature, float, Mana );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangeDelegateSignature, float, MaxMana );
/**
 * 
 */
UCLASS()
class AURA_API UOverlayWidgetController : public UMyWidgetController
{
	GENERATED_BODY()

	public:
	void BroadcastInitialValues();

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeDelegateSignature OnHealthChangeDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnMaxHealthChangeDelegateSignature OnMaxHealthChangeDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnManaChangeDelegateSignature OnManaChangeDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnMaxManaChangeDelegateSignature OnMaxManaChangeDelegate;

	UPROPERTY()
	UMyAttributeSet* MyAttributeSet;

	UMyAttributeSet* GetMyAttributeSet();
	
};
