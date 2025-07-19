// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
USTRUCT()
struct FWidgetControllerParams
{
	GENERATED_BODY()
	public:
	
	FWidgetControllerParams(){};
	FWidgetControllerParams(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS ): PlayerController(PC),PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS)
	{
	};
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	APlayerState* PlayerState;
	
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UAttributeSet* AttributeSet;

};
UCLASS(Blueprintable, BlueprintType)
class AURA_API UMyWidgetController : public UObject
{
	GENERATED_BODY()

	public:
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerParamsSet();

	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UAttributeSet* AttributeSet;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	APlayerState* PlayerState;

	protected:
	virtual void BroadcastInitialValues();
	virtual void BindCallbackToDependencies();
};
