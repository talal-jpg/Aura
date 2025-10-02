// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Data/DA_AttributeInfo.h"
#include "UI/WidgetController/MyWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
 * 
 */


class UDA_AttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeBroadcastAttributeInfoDelegateSignature,FAttributeInfo,AttributeInfo);

UCLASS(Blueprintable, BlueprintType)
class AURA_API UAttributeMenuWidgetController : public UMyWidgetController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues() override;

	UFUNCTION(BlueprintCallable)
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(EditAnywhere)
	UDA_AttributeInfo* DA_AttributeInfo;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeBroadcastAttributeInfoDelegateSignature OnAttributeChangeBroadcastAttributeInfoDelegate;
};
