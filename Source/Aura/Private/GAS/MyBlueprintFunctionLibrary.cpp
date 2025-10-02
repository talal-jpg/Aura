// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/MyBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "MyAbilityTypes.h"
#include "MyGameModeBase.h"
#include "GAS/Data/DA_DefaultEnemyAttributes.h"
#include "GAS/GameplayAbility/MyGameplayAbility.h"
#include "Interface/CombatInterface.h"
#include "Player/MyPlayerState.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"

UAttributeMenuWidgetController* UMyBlueprintFunctionLibrary::GetAttributeMenuWidgetController(
	UObject* WorldContextObject)
{
		APlayerController* PC=UGameplayStatics::GetPlayerController(WorldContextObject, 0);
		AMyHUD* MyHUD=PC->GetHUD<AMyHUD>();
		UAttributeMenuWidgetController* AttributeMenuWidgetController=MyHUD->GetAttributeMenuWidgetController();
		AMyPlayerState* PS=PC->GetPlayerState<AMyPlayerState>();
		UAbilitySystemComponent* ASC=PS->AbilitySystemComponent;
		UAttributeSet* AS= PS->AttributeSet;
		
		FWidgetControllerParams WidgetControllerParams=FWidgetControllerParams(PC,PS,ASC,AS);
		AttributeMenuWidgetController->SetWidgetControllerParams(WidgetControllerParams);
	
		return AttributeMenuWidgetController;
}

void UMyBlueprintFunctionLibrary::InitializeDefaultAttributes(ECharacterClass InCharacterClass , UObject* WorldContextObject,UAbilitySystemComponent* ASC,float Level)
{
	AMyGameModeBase* MyGameModeBase=Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!MyGameModeBase) return;
	UDA_DefaultEnemyAttributes* DefaultEnemyAttributesInfo=MyGameModeBase->DefaultEnemyAttributesInfo;

	AActor* AvatarActor=ASC->GetAvatarActor();
	
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttrs=DefaultEnemyAttributesInfo->GetCharacterClassInfo(InCharacterClass)->DefaultPrimaryAttributes;
	TSubclassOf<UGameplayEffect> DefSecAttrs=DefaultEnemyAttributesInfo->DefaultSecondaryAttributes;
	TSubclassOf<UGameplayEffect> DefVitalAttrs=DefaultEnemyAttributesInfo->DefaultVitalAttributes;

	FGameplayEffectContextHandle EffectContextHandle=ASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(AvatarActor);
	FGameplayEffectSpecHandle PrimAttrsEffectSpecHandle=ASC->MakeOutgoingSpec(DefaultPrimaryAttrs,Level,EffectContextHandle);
	FGameplayEffectSpecHandle SecAttrsEffectSpecHandle=ASC->MakeOutgoingSpec(DefSecAttrs,Level,EffectContextHandle);
	FGameplayEffectSpecHandle VitalAttrsEffectSpecHandle=ASC->MakeOutgoingSpec(DefVitalAttrs,Level,EffectContextHandle);

	ASC->ApplyGameplayEffectSpecToSelf(*PrimAttrsEffectSpecHandle.Data.Get());
	ASC->ApplyGameplayEffectSpecToSelf(*SecAttrsEffectSpecHandle.Data.Get());
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttrsEffectSpecHandle.Data.Get());
	
}

void UMyBlueprintFunctionLibrary::GiveStartupAbilities(UObject* WorldContextObject, UAbilitySystemComponent* ASC,ECharacterClass CharacterClass)
{
	AMyGameModeBase* MyGameMode=Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!MyGameMode)return;
	UDA_DefaultEnemyAttributes* DefaultEnemyAttrs= MyGameMode->DefaultEnemyAttributesInfo;
	for (auto AbilityClass:DefaultEnemyAttrs->CommonAbilities)
	{
		FGameplayAbilitySpec GASpec=FGameplayAbilitySpec(AbilityClass,1);
		if (UMyGameplayAbility* MyGA=Cast<UMyGameplayAbility>(GASpec.Ability))
		{
			GASpec.GetDynamicSpecSourceTags().AddTag(MyGA->StartupInputTag);
			ASC->GiveAbility(GASpec);
		}
	}
	
	for (auto AbilityClass:DefaultEnemyAttrs->GetInfoFromClass(CharacterClass).SpecificAbilitiesPerClass)
	{
		FGameplayAbilitySpec GASpec=FGameplayAbilitySpec(AbilityClass,1);
		if (UMyGameplayAbility* MyGA=Cast<UMyGameplayAbility>(GASpec.Ability))
		{
			GASpec.GetDynamicSpecSourceTags().AddTag(MyGA->StartupInputTag);
			ASC->GiveAbility(GASpec);
		}
	}
}

void UMyBlueprintFunctionLibrary::GetLivePlayersWithinARadius(UObject* WorldContextObject,
	TArray<AActor*>& OutOverlappingActors,const TArray<AActor*>& ActorsToIgnore, const FVector& SphereOrigin, float Radius)
{
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActors(ActorsToIgnore);

	FCollisionObjectQueryParams CollisionObjectQueryParams;

	TArray<FOverlapResult> OverlapResults;
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		World->OverlapMultiByObjectType(OverlapResults, SphereOrigin,FQuat::Identity,CollisionObjectQueryParams,FCollisionShape::MakeSphere(Radius),CollisionQueryParams);
		for (FOverlapResult& OverlapResult : OverlapResults)
		{
			bool bImplementsCombatInterface=OverlapResult.GetActor()->Implements<UCombatInterface>();
			if (bImplementsCombatInterface)
			{
				OutOverlappingActors.AddUnique(OverlapResult.GetActor());
			}
		}
		
	}
	
}

bool UMyBlueprintFunctionLibrary::bIsFriendly(AActor* ActorA, AActor* ActorB)
{
	bool bIsFriendly=false;
	for (FName Tag:ActorA->Tags)
	{
		bIsFriendly=ActorB->ActorHasTag(Tag);
	}
	return bIsFriendly;
}

bool UMyBlueprintFunctionLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FMyGameplayEffectContext* MyGameplayEffectContext = static_cast<const FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return MyGameplayEffectContext->IsBlockedHit();
	}
	return false;
}

bool UMyBlueprintFunctionLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FMyGameplayEffectContext* MyGameplayEffectContext = static_cast<const FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return MyGameplayEffectContext->IsCriticalHit();
	}
	return false;
}

void UMyBlueprintFunctionLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bIsBlocked)
{
	if (FMyGameplayEffectContext* MyGameplayEffectContext=static_cast<FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		MyGameplayEffectContext->SetIsBlockedHit(bIsBlocked);
	}
}

void UMyBlueprintFunctionLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bIsCritical)
{
	if (FMyGameplayEffectContext* MyGameplayEffectContext=static_cast<FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		MyGameplayEffectContext->SetIsCriticalHit(bIsCritical);
	}
}


