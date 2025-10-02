// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT()
struct FWidgetControllerParams
{
	GENERATED_BODY()
	FWidgetControllerParams(){};
	FWidgetControllerParams(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS):PlayerController(PC),PlayerState(PS),AbilitySystemComponent(ASC),AttributeSet(AS)
	{};
	public:
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	APlayerState* PlayerState;

	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UAttributeSet* AttributeSet;
};
/**
 * 
 */
UCLASS()
class AURA_API UMyWidgetController : public UObject
{
public:
	GENERATED_BODY()

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	APlayerState* PlayerState;
	
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UAttributeSet* AttributeSet;
	
	void SetWidgetControllerParams(const FWidgetControllerParams& Params);

	virtual void BindCallbacksToDependencies();

	virtual void BroadcastInitialValues();

	
};
