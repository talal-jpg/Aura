// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/MyWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
class UMyAttributeSet;

USTRUCT()
struct FPopUpWidgetInfo: public FTableRowBase
{
	GENERATED_BODY()
	public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GE")
	FGameplayTag EffectMessageTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GE")
	FText Message;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GE")
	TSubclassOf<UUserWidget> Widget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GE")
	UTexture2D* Image;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeDelegateSignature, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangeDelegateSignature, float, MaxHealth );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangeDelegateSignature, float, Mana );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangeDelegateSignature, float, MaxMana );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayEffectAppliedBroadcastPopUpWidgetInfoDelegateSignature, FPopUpWidgetInfo,PopUpWidgetInfo);
/**
 * 
 */
UCLASS()
class AURA_API UOverlayWidgetController : public UMyWidgetController
{
	GENERATED_BODY()

	public:
	virtual void BroadcastInitialValues() override;
	
	virtual void BindCallbackToDependencies() override;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeDelegateSignature OnHealthChangeDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnMaxHealthChangeDelegateSignature OnMaxHealthChangeDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnManaChangeDelegateSignature OnManaChangeDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnMaxManaChangeDelegateSignature OnMaxManaChangeDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnGameplayEffectAppliedBroadcastPopUpWidgetInfoDelegateSignature OnGameplayEffectAppliedBroadcastPopUpWidgetInfoDelegate;

	UPROPERTY()
	UMyAttributeSet* MyAttributeSet;

	UMyAttributeSet* GetMyAttributeSet();

	void OnHeathChange(const FOnAttributeChangeData& HealthData);
	void OnMaxHealthChange(const FOnAttributeChangeData& MaxHealthData);
	void OnManaChange(const FOnAttributeChangeData& ManaData);
	void OnMaxManaChange(const FOnAttributeChangeData& MaxManaData);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* DT_PopUpWidgetInfo;
	
	
};
