// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

class UMyUserWidget;
struct FWidgetControllerParams;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API AMyHUD : public AHUD
{
	GENERATED_BODY()

	public:
	void InitOverlay(const FWidgetControllerParams& Params );

	UPROPERTY()
	UOverlayWidgetController* OverlayWidgetController;

	UPROPERTY()
	UMyUserWidget* OverlayUserWidget;

	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY(EditAnywhere,Category="UI")
	TSubclassOf<UMyUserWidget> OverlayUserWidgetClass;
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
};
