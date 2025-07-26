// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "CharacterBase.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class AURA_API ACharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAttributeSet* AttributeSet;

	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// InitializeDefaultAttrs
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void InitializePrimaryAttributes();

	void InitializeSecondaryAttributes();

	void InitializeVitalAttributes();

	void ApplyEffect(TSubclassOf<UGameplayEffect> EffectClass);

	virtual int GetPlayerLevel() override;
};
