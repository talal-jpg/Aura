// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interface/CursorHitInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "CharacterEnemy.generated.h"

class UMyUserWidget;
class UWidgetComponent;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AURA_API ACharacterEnemy : public ACharacterBase , public ICursorHitInterface   
{
	GENERATED_BODY()
	public:
	ACharacterEnemy();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Highlight() override;
	virtual void UnHighlight() override;

	UPROPERTY(BlueprintReadWrite)
	bool bIsHighlighted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeDelegateSignature OnHealthChangeDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnMaxHealthChangeDelegateSignature OnMaxHealthChangeDelegate;

	UPROPERTY(BlueprintReadWrite)
	UMyUserWidget* HealthBar;


	UPROPERTY(EditAnywhere )
	int PlayerLevel=1;
	
	virtual int GetPlayerLevel() override;
};


