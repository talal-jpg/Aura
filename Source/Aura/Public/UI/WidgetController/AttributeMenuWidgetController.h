// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Data/AttributeInfoDataAsset.h"
#include "UI/WidgetController/MyWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfoDataAsset;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeBroadcastAttributeInfoDelegateSignature,FAttributeInfoStruct, AttributeInfo);

UCLASS()
class AURA_API UAttributeMenuWidgetController : public UMyWidgetController
{
	GENERATED_BODY()

	public:

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues() override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAttributeInfoDataAsset* DA_AttributeInfo;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeBroadcastAttributeInfoDelegateSignature OnAttributeChangeBroadcastAttributeInfoDelegate;
	
};
