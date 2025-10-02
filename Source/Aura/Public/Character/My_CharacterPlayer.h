// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "AbilitySystemInterface.h"
#include "My_CharacterPlayer.generated.h"

class UGameplayAbility;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class AURA_API AMy_CharacterPlayer : public ACharacterBase , public IAbilitySystemInterface
{
	GENERATED_BODY()
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	void InitAbilityActorInfo();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitializeDefaultAttributes() override;

	void ApplyEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass);


};
