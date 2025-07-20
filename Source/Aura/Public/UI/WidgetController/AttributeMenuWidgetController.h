// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/MyWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfoDataAsset;
/**
 * 
 */
UCLASS()
class AURA_API UAttributeMenuWidgetController : public UMyWidgetController
{
	GENERATED_BODY()

	public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UAttributeInfoDataAsset> AttributeInfoDataAsset;

	virtual void BroadcastInitialValues() override;
	
};
