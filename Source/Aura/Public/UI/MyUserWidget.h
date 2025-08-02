// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

class UMyWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
	
	UPROPERTY(BlueprintReadWrite)
	UObject* WidgetController;

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

};
