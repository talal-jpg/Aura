// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

class UAttributeMenuWidgetController;
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

	virtual void BeginPlay() override;

	UPROPERTY()
	UOverlayWidgetController* OverlayWidgetController;

	UPROPERTY()
	UAttributeMenuWidgetController* AttributeMenuWidgetController;

	UPROPERTY()
	UMyUserWidget* OverlayUserWidget;

	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY(EditAnywhere,Category="UI")
	TSubclassOf<UMyUserWidget> OverlayUserWidgetClass;

	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
};
