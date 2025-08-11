// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MyAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
UCLASS()
class AURA_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UMyAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// MetaAttributes
	UPROPERTY(BlueprintReadOnly,Category="Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,IncomingDamage)

	// VitalAttributes
	UPROPERTY(ReplicatedUsing= OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Health)
	
	UPROPERTY(ReplicatedUsing= OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Mana)

	// PrimaryAttributes
	UPROPERTY(ReplicatedUsing= OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Strength)

	UPROPERTY(ReplicatedUsing= OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Intelligence)

	UPROPERTY(ReplicatedUsing= OnRep_Resilience)
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Resilience)

	UPROPERTY(ReplicatedUsing= OnRep_Vigor)
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Vigor)

	// SecondaryAttributes
	UPROPERTY(ReplicatedUsing= OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Armor)

	UPROPERTY(ReplicatedUsing= OnRep_ArmorPenetration)
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,ArmorPenetration)

	UPROPERTY(ReplicatedUsing= OnRep_BlockChance)
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,BlockChance)

	UPROPERTY(ReplicatedUsing= OnRep_CriticalHitChance)
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,CriticalHitChance)
	
	UPROPERTY(ReplicatedUsing= OnRep_CriticalHitDamage)
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,CriticalHitDamage)
	
	UPROPERTY(ReplicatedUsing= OnRep_CriticalHitResistance)
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,CriticalHitResistance)
	
	UPROPERTY(ReplicatedUsing= OnRep_HealthRegeneration)
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,HealthRegeneration)
	
	UPROPERTY(ReplicatedUsing= OnRep_ManaRegeneration)
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,ManaRegeneration)
	
	UPROPERTY(ReplicatedUsing= OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,MaxHealth)
	
	UPROPERTY(ReplicatedUsing= OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,MaxMana)
	
	// VitalAttributes
	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_Health(const FGameplayAttributeData& OldValue) const;
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_Mana(const FGameplayAttributeData& OldValue) const;
	
	// PrimaryAttributes
	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_Strength(const FGameplayAttributeData& OldValue) const;

	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_Intelligence(const FGameplayAttributeData& OldValue) const;
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_Resilience(const FGameplayAttributeData& OldValue) const;
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_Vigor(const FGameplayAttributeData& OldValue) const;

	// SecondaryAttributes
	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_Armor(const FGameplayAttributeData& OldValue) const;

	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldValue) const;
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_BlockChance(const FGameplayAttributeData& OldValue) const;
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldValue) const;
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldValue) const;
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldValue) const;
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldValue) const;
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldValue) const;
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue) const;
	
	TMap<FGameplayTag,FGameplayAttribute> AttributeGameplayTagMap;
};
