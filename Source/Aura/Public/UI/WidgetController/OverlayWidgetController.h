// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GAS/Data/DA_AbilityInfo.h"
#include "UI/MyUserWidget.h"
#include "UI/WidgetController/MyWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UDA_AbilityInfo;
class UDA_AttributeInfo;
class UMyAbilitySystemComponent;
class UMyUserWidget;

USTRUCT()
struct FPopupWidgetRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FGameplayTag MessageTag;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FText MessageText;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UTexture2D* MessageImage;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<UMyUserWidget> PopUpUserWidgetClass;
};

class UMyAttributeSet;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeBrodcastValDelegateSignature, float, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEffectAppliedBroadcastPopupWidgetRowDelegateSignature, FPopupWidgetRow, PopupWidgetRow);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilitiesGivenBrodcastAbilityInfoDelegateSignature, FAbilityInfo, AbilityInfo);


UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UMyWidgetController
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeBrodcastValDelegateSignature OnHealthChangeBroadcastValDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeBrodcastValDelegateSignature OnMaxHealthChangeBroadcastValDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeBrodcastValDelegateSignature OnManaChangeBroadcastValDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeBrodcastValDelegateSignature OnMaxManaChangeBroadcastValDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnEffectAppliedBroadcastPopupWidgetRowDelegateSignature OnEffectAppliedBroadcastPopupWidgetRowDelegate;
	
	virtual void BindCallbacksToDependencies() override;

	virtual void BroadcastInitialValues() override;

	UPROPERTY()
	UMyAttributeSet* MyAttributeSet;

	UMyAttributeSet* GetMyAttributeSet();

	UPROPERTY(EditAnywhere)
	UDataTable* PopUpWidgetInfo;

	void OnInitializeStartupAbilities(UMyAbilitySystemComponent* AbilitySystemComponent);

	UPROPERTY(EditAnywhere)
	UDA_AbilityInfo* DA_AbilityInfo;

	UPROPERTY(BlueprintAssignable)
	FOnAbilitiesGivenBrodcastAbilityInfoDelegateSignature OnAbilitiesGivenBroadcastAbilityInfoDelegate;
};
