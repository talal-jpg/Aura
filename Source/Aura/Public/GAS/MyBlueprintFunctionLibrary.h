// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MyHUD.h"
#include "MyBlueprintFunctionLibrary.generated.h"

struct FGameplayEffectContextHandle;
class UAbilitySystemComponent;
enum class ECharacterClass : uint8;
class AMyHUD;
/**
 * 
 */
UCLASS()
class AURA_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(UObject* WorldContextObject);


public:
	static void InitializeDefaultAttributes(ECharacterClass InCharacterClass , UObject* WorldContextObject,UAbilitySystemComponent* ASC,float Level);

	UFUNCTION(BlueprintCallable)
	static void GiveStartupAbilities(UObject* WorldContextObject, UAbilitySystemComponent* ASC,ECharacterClass CharacterClass);

	UFUNCTION(BlueprintCallable)
	static void GetLivePlayersWithinARadius(UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors,const TArray<AActor*>& ActorsToIgnore,const FVector& SphereOrigin, float Radius);

	UFUNCTION(BlueprintCallable)
	static bool bIsFriendly(AActor* ActorA, AActor* ActorB);

	UFUNCTION(BlueprintPure)
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure)
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable)
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bIsBlocked);

	UFUNCTION(BlueprintCallable)
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bIsCritical);
};
