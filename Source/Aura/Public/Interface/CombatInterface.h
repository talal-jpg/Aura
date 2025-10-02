// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FTaggedMontage
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGameplayTag AttackSocketTag;
	
};
class AURA_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetSocketLocation(FName SocketName);
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FTaggedMontage GetTaggedAttackMontageStruct();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	AActor* GetCombatTarget();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void SetCombatTarget(AActor* NewCombatTarget);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void SetMotionWarpingTarget(FVector NewTargetLocation);

	virtual void Die()=0;

	
};
