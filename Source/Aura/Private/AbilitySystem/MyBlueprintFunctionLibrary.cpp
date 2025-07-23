// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MyBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerState.h"
#include "UI/MyHUD.h"
#include "UI/WidgetController/MyWidgetController.h"

class AMyPlayerState;
UAttributeMenuWidgetController* UMyBlueprintFunctionLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PC=UGameplayStatics::GetPlayerController(WorldContextObject,0);
	AMyPlayerState* PS=PC->GetPlayerState<AMyPlayerState>();
	UAbilitySystemComponent* ASC = PS->AbilitySystemComponent;
	UAttributeSet* AS= PS->AttributeSet;
	FWidgetControllerParams WCParams= FWidgetControllerParams(PC,PS,ASC,AS);
	UAttributeMenuWidgetController* AttributeMenuWidgetController= Cast<AMyHUD>(PC->GetHUD())->GetAttributeMenuWidgetController(WCParams);
	return AttributeMenuWidgetController;
}
