// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

class UAttributeMenuWidgetController;
class UMyUserWidget;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API AMyHUD : public AHUD
{
	GENERATED_BODY()

	public: 
	void InitOverlay();

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController() const;

	UPROPERTY()
	mutable UAttributeMenuWidgetController* AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMyWidgetController> AttributeMenuWidgetControllerClass;
	
	UPROPERTY()
	UOverlayWidgetController* OverlayWidgetController;

	UPROPERTY()
	UMyUserWidget* OverlayUserWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMyUserWidget> OverlayUserWidgetClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMyWidgetController> OverlayWidgetControllerClass;
};
