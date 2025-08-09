// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MyBlueprintFunctionLibrary.h"
#include "AbilitySystemComponent.h"
#include "MyGameModeBase.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/CharacterBase.h"
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

void UMyBlueprintFunctionLibrary::InitializeDefaultCharacterAttributes(UObject* WorldContextObject,
	ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* AbilitySystemComponent)
{
	UCharacterClassInfo* CharacterClassInfo=Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject))->DA_CharacterClassInfo;
	FCharacterClassDefaultInfo CharClassDefInfo=CharacterClassInfo->GetCharacterClassDefaultInfo(CharacterClass);

	AActor* AvatarActor= AbilitySystemComponent->GetAvatarActor();
	
	FGameplayEffectContextHandle EffectContextHandle=AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(AvatarActor);
	FGameplayEffectSpecHandle EffectSpecHandle=AbilitySystemComponent->MakeOutgoingSpec(CharClassDefInfo.PrimaryAttributes,Level,EffectContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	FGameplayEffectContextHandle EffectContextHandleSecondary=AbilitySystemComponent->MakeEffectContext();
	EffectContextHandleSecondary.AddSourceObject(AvatarActor);
	FGameplayEffectSpecHandle EffectSpecHandleSecondary=AbilitySystemComponent->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes,Level,EffectContextHandleSecondary);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandleSecondary.Data.Get());

	
	FGameplayEffectContextHandle EffectContextHandleVital=AbilitySystemComponent->MakeEffectContext();
	EffectContextHandleVital.AddSourceObject(AvatarActor);
	FGameplayEffectSpecHandle EffectSpecHandleVital=AbilitySystemComponent->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes,Level,EffectContextHandleVital);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandleVital.Data.Get());
}
